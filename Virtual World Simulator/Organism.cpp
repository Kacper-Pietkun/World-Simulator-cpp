#include <iostream>
#include "Organism.h"

Organism::Organism(World& _world, Position _position, string _class_id, int _strength,
	int _initiative, int _age, bool _is_ability_active, int _rounds_of_ability)
	: world(_world), position(_position), class_id(_class_id), strength(_strength),
	initiative(_initiative), age(_age), is_ability_active(_is_ability_active), rounds_of_ability(_rounds_of_ability)
{}

int Organism::howManyNotBusyPlaces() const
{
	int count = 0;
	Position temp_pos = position;
	if (world.isThisSpotInsideMap(temp_pos + Position(0, -1)) == true && world.isThisSpotFree(temp_pos + Position(0, -1)) == true) // UP
		count++;
	if (world.isThisSpotInsideMap(temp_pos + Position(1, 0)) == true && world.isThisSpotFree(temp_pos + Position(1, 0)) == true) // RIGHT
		count++;
	if (world.isThisSpotInsideMap(temp_pos + Position(0, 1)) == true && world.isThisSpotFree(temp_pos + Position(0, 1)) == true) // DOWN
		count++;
	if (world.isThisSpotInsideMap(temp_pos + Position(-1, 0)) == true && world.isThisSpotFree(temp_pos + Position(-1, 0)) == true) // LEFT
		count++;
	return count;
}

Position Organism::getNotBusyPlace() const
{
	if (howManyNotBusyPlaces() == 0) // There is no space for breeding
		return position;

	Position my_position = position;
	Position new_position;
	int rand_delta_x, rand_delta_y; // values -1, 0, 1
	int x_or_y;
	do
	{
		rand_delta_x = rand() % 3 - 1; // to get -1 or 0 or 1
		rand_delta_y = rand() % 3 - 1; // to get -1 or 0 or 1
		x_or_y = rand() % 2;
		if (x_or_y == X)
			new_position = my_position + Position(rand_delta_x, 0);
		else
			new_position = my_position + Position(0, rand_delta_y);
	} while (world.isThisSpotInsideMap(new_position) == false || world.isThisSpotFree(new_position) == false);

	return new_position;
}

int Organism::getAge() const
{
	return age;
}

void Organism::setAge(int age)
{
	this->age = age;
}

int Organism::getInitiative() const
{
	return initiative;
}

int Organism::getStrength() const
{
	return strength;
}

void Organism::setStrength(int _strength)
{
	strength = _strength;
}

string Organism::getClassId() const
{
	return class_id;
}

Position Organism::getPosition() const
{
	return position;
}

void Organism::setPosition(Position pos)
{
	position = pos;
}

bool Organism::getIsAbilityActive() const
{
	return is_ability_active;
}

int Organism::getRoundsOfAbility() const
{
	return rounds_of_ability;
}