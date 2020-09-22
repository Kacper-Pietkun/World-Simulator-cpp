#include "Plant.h"

Plant::Plant(World& _world, Position _position, string _class_id, int _spawn_chance, int _spawn_attempts, int _strength, int _initiative, int _age)
	:Organism(_world, _position, _class_id, _strength, _initiative, _age)
{
	spawn_chance = _spawn_chance;
	spawn_attempts = _spawn_attempts;
}


void Plant::action()
{
	InfoMessenger& info_messenger = world.getInfoMessenger(); // get reference to information messenger to add information to round raport 
	bool is_spawning = false;
	int draw;
	Position child_position;
	killAllNearbyAnimals(); // Hogweed feature
	for (int i = 0; i < spawn_attempts; i++)
	{
		draw = rand() % PERCENT_100;
		if (draw < spawn_chance) // Checks if plant will spread
		{
			child_position = getNotBusyPlace();
			if (!(child_position == position))  // check if parent has free space (positions will be equal if there is not any free position)
			{
				spawnChild(child_position);
				info_messenger.addNewPlantSpawnedInfo(class_id);
			}
			//else info_messenger.addNewPlantNotSpawnedInfo(class_id);

		}
	}
}

bool Plant::collision(Organism* attacker)
{
	InfoMessenger& info_messenger = world.getInfoMessenger(); // get reference to information messenger to add information to round raport 
	info_messenger.addAnimalEatsPlant(attacker, this);
	return false; // standard plant does nothing to an animal
}

void Plant::killAllNearbyAnimals()
{
	// This is just implementation, for plants that do not kill animals that are nearby
}