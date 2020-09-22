#include <iostream>
#include "Hogweed.h"
#include "Constant.h"
#include "Animal.h"

using namespace std;

Hogweed::Hogweed(World& _world, Position _position, string _class_id, int _spawn_chance, int _spawn_attempts, int _strength, int _initiative, int _age)
	:Plant(_world, _position, _class_id, _spawn_chance, _spawn_attempts, _strength, _initiative, _age)
{}

void Hogweed::draw() const
{
	cout << SYMBOL_HOGWEED;
}

void Hogweed::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Hogweed(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array
	world.makeEveryoneOlder();
}

bool Hogweed::collision(Organism* attacker)
{
	InfoMessenger& info_messenger = world.getInfoMessenger(); // get reference to information messenger to add information to round raport 
	info_messenger.addPlantKillsAnimal(attacker, this);
	return true;
}

void Hogweed::killAllNearbyAnimals()
{
	InfoMessenger& info_messenger = world.getInfoMessenger(); // get reference to information messenger to add information to round raport 
	Organism* org;


	org = world.isThisSpotInsideMap(position + Position(0, -1)) == true ? world.getOrganismAt(position + Position(0, -1)) : NULL; // UP
	if (org != NULL && dynamic_cast<Animal*>(org) != NULL)
	{
		world.killOrganismAt(org->getPosition());
		info_messenger.addHogweedKillsInZone(org);
	}
	org = world.isThisSpotInsideMap(position + Position(0, 1)) == true ? world.getOrganismAt(position + Position(0, 1)) : NULL; // DOWN
	if (org != NULL && dynamic_cast<Animal*>(org) != NULL)
	{
		world.killOrganismAt(org->getPosition());
		info_messenger.addHogweedKillsInZone(org);
	}
	org = world.isThisSpotInsideMap(position + Position(1, 0)) == true ? world.getOrganismAt(position + Position(1, 0)) : NULL; // RIGHT
	if (org != NULL && dynamic_cast<Animal*>(org) != NULL)
	{
		world.killOrganismAt(org->getPosition());
		info_messenger.addHogweedKillsInZone(org);
	}
	org = world.isThisSpotInsideMap(position + Position(-1, 0)) == true ? world.getOrganismAt(position + Position(-1, 0)) : NULL; // LEFT
	if (org != NULL && dynamic_cast<Animal*>(org) != NULL)
	{
		world.killOrganismAt(org->getPosition());
		info_messenger.addHogweedKillsInZone(org);
	}
}

