#include <iostream>
#include "Belladonna.h"
#include "Constant.h"

using namespace std;

Belladonna::Belladonna(World& _world, Position _position, string _class_id, int _spawn_chance, int _spawn_attempts, int _strength, int _initiative, int _age)
	:Plant(_world, _position, _class_id, _spawn_chance, _spawn_attempts, _strength, _initiative, _age)
{}

void Belladonna::draw() const
{
	cout << SYMBOL_BELLADONNA;
}

void Belladonna::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Belladonna(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array
	world.makeEveryoneOlder();
}

bool Belladonna::collision(Organism* attacker)
{
	InfoMessenger& info_messenger = world.getInfoMessenger(); // get reference to information messenger to add information to round raport 
	info_messenger.addPlantKillsAnimal(attacker, this);
	return true;
}

