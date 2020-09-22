#include <iostream>
#include <string>
#include "Animal.h"
#include "Plant.h"
#include "Human.h"
#include "Constant.h"

Animal::Animal(World& _world, Position _position, string _class_id, int _strength, int _initiative, int _age, bool _is_ability_active, int _rounds_of_ability)
	:Organism(_world, _position, _class_id, _strength, _initiative, _age, _is_ability_active, _rounds_of_ability)
{}

Position Animal::getPositionToMove(int direction, int how_many_steps) const
{
	Position new_position = position; // We check if our destination position is free, but we return new position which is only one step away from an animal, because it will go to its destination gradually
	if (direction == UP && world.isThisSpotInsideMap(new_position + Position(0, -how_many_steps)) == true)
		new_position = new_position + Position(0, -1);
	else if (direction == RIGHT && world.isThisSpotInsideMap(new_position + Position(how_many_steps, 0)) == true)
		new_position = new_position + Position(1, 0);
	else if (direction == DOWN && world.isThisSpotInsideMap(new_position + Position(0, how_many_steps)) == true)
		new_position = new_position + Position(0, 1);
	else if (direction == LEFT && world.isThisSpotInsideMap(new_position + Position(-how_many_steps, 0)) == true)
		new_position = new_position + Position(-1, 0);
	return new_position;
}

Position Animal::getRandomPositionToGo(int how_many_steps) const
{
	Position new_position;
	int direction;
	do
	{
		direction = rand() % 4;
		new_position = getPositionToMove(direction, how_many_steps);
	} while (new_position == position || isThereStrongerOrganism(new_position) == true); // it means it generated position outside of the map, so repeat rand()
	return new_position;
}

Position Animal::getPositionForHumanToGo(int how_many_steps) const
{
	int key = readKeyArrowInput();
	switch (key)
	{
	case KEY_UP:
		return getPositionToMove(UP, how_many_steps);
	case KEY_DOWN:
		return getPositionToMove(DOWN, how_many_steps);
	case KEY_LEFT:
		return getPositionToMove(LEFT, how_many_steps);
	case KEY_RIGHT:
		return getPositionToMove(RIGHT, how_many_steps);
	case KEY_ENTER:
		return position; // Stay in this place
	}
	return position;
}


void Animal::action()
{
	bool collision_result = CAN_GO_FURTHER;
	Position new_position;
	Position delta_position; // This position will tell to which position animal goes (helpful when animal go more than one step)

	if (world.getKeyAbilityActiveInput() == true && dynamic_cast<Human*>(this) != NULL) // If it is human then activate super ability
	{
		activateSuperAbility();
		world.setKeyActiveAbility(false);
	}

	int how_many_steps = howManySteps();
	int how_many_accessible_positions = numberOfAccessiblePositions(how_many_steps);

	if (how_many_accessible_positions == 0)
		return; // animal doesn't have where to move
	if (isItAbleToMove() == false)
		return; // won't move this round

	if (dynamic_cast<Human*>(this) == NULL) // draw position for animal other than human
		new_position = getRandomPositionToGo(how_many_steps);
	else // Human moves, then he moves according to the clicked key arrow
		new_position = getPositionForHumanToGo(how_many_steps);

	if (new_position == position)
		return;
	delta_position = new_position - position;
	for (int i = 0; i < how_many_steps; i++) // Loop for number of steps that organism will do
	{
		if (world.isThisSpotFree(new_position)) // Free spot, just go there
			world.changeOrganismPosition(this, position, new_position);
		else // Spot is occupied by another organisms - colission
			collision_result = collision(world.getOrganismAt(new_position));

		if (collision_result == STOP)
			break; // Don't go further because environment doesn't allow
		new_position = position + delta_position;
	}
}

bool Animal::collision(Organism* collision_organism)
{
	InfoMessenger& info_messenger = world.getInfoMessenger(); // get reference to information messenger to add information to round raport 

	if (getClassId() == collision_organism->getClassId()) // It means breeding
	{
		Position child_position = collision_organism->getNotBusyPlace();
		if (!(child_position == collision_organism->getPosition()))  // check if first parent has free space
		{
			collision_organism->spawnChild(child_position);
			info_messenger.addNewAnimalBornedInfo(class_id);
			return STOP;
		}
		else // check if second parent has free space
		{
			child_position = getNotBusyPlace();
			if (child_position == collision_organism->getPosition())
			{
				spawnChild(child_position);
				info_messenger.addNewAnimalBornedInfo(class_id);
				return STOP;
			}
		}
		// else No space for the child
		//info_messenger.addNewAnimalNotBornedInfo(class_id);
	}
	else if (dynamic_cast<Animal*>(collision_organism) != NULL) // It means fighting
	{
		Animal* defender = dynamic_cast<Animal*>(collision_organism); // Changing pointer type so we can call functions only available for Animal
		Organism* dies = NULL;
		if (defender->defendItself(this) == true)
		{
			info_messenger.addDefendedItslefFrom(this, defender);
			return STOP; // Defender defends itslef from being eaten
		}
		Position position_for_winner = defender->getPosition(); // winner of the fight will go to this place (or just stay there if organism defended themself)

		if (runFromBattle() == true)
		{
			world.changeOrganismPosition(this, position, getNotBusyPlace());
			info_messenger.addAnimalRanAway(this, defender, this);
			return STOP; // If this animal ran away then they don't want to attack the same organism again
		}
		else if (defender->runFromBattle())
		{
			world.changeOrganismPosition(defender, defender->getPosition(), defender->getNotBusyPlace());
			info_messenger.addAnimalRanAway(this, defender, defender);
			return CAN_GO_FURTHER; // If defender ran away then this animal can go further
		}

		if (strength >= defender->getStrength()) // if strengths are equal then attacker wins
		{
			dies = defender;
			info_messenger.addAnimalKilledByAnimal(this, defender, ATTACKER);
		}
		else
		{
			dies = this;
			info_messenger.addAnimalKilledByAnimal(this, defender, DEFENDER);
		}

		world.killOrganismAt(dies->getPosition());
		world.changeOrganismPosition(this, position, position_for_winner);
		if (dies == this)
			return STOP;
		return CAN_GO_FURTHER;
	}
	else if (dynamic_cast<Plant*>(collision_organism) != NULL) // Plant will be eaten
	{
		bool will_die = false;
		Plant* plant = dynamic_cast<Plant*>(collision_organism);
		Organism* dies = plant;
		will_die = plant->collision(this);
		world.killOrganismAt(dies->getPosition()); // Plant always dies, because it was eaten
		if (will_die == true)
		{
			world.killOrganismAt(position); // Animal die, after eating this plant;
			return STOP;
		}
		else // else it goes to the plant's position
		{
			world.changeOrganismPosition(this, position, plant->getPosition());
			return CAN_GO_FURTHER;
		}
	}
	return STOP;
}

bool Animal::isThereStrongerOrganism(Position position) const
{
	return false;
}

bool Animal::isItAbleToMove() const
{
	return true;
}

bool Animal::defendItself(Organism* attacker) const
{
	return false;
}

int Animal::howManySteps()
{
	return 1;
}

bool Animal::runFromBattle() const
{
	return false;
}

void Animal::spawnChild(Position child_position) const
{
	// For animals that won't have offspring
}

int Animal::readKeyArrowInput() const
{
	return KEY_ENTER;
}

void Animal::activateSuperAbility()
{
	// Normal animals do not have any super ability
}

int Animal::numberOfAccessiblePositions(int how_many_steps) const
{
	int number = 0;
	if (world.isThisSpotInsideMap(position + Position(0, -how_many_steps)) == true && isThereStrongerOrganism(position + Position(0, -how_many_steps)) == false) // UP
		number++;
	if (world.isThisSpotInsideMap(position + Position(how_many_steps, 0)) == true && isThereStrongerOrganism(position + Position(how_many_steps, 0)) == false) // RIGHT
		number++;
	if (world.isThisSpotInsideMap(position + Position(0, how_many_steps)) == true && isThereStrongerOrganism(position + Position(0, how_many_steps)) == false) // DOWN
		number++;
	if (world.isThisSpotInsideMap(position + Position(-how_many_steps, 0)) == true && isThereStrongerOrganism(position + Position(-how_many_steps, 0)) == false) // LEFT
		number++;
	return number;
}