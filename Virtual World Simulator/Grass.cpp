#include <iostream>
#include "Grass.h"
#include "Constant.h"

using namespace std;

Grass::Grass(World& _world, Position _position, string _class_id, int _spawn_chance, int _spawn_attempts, int _strength, int _initiative, int _age)
	:Plant(_world, _position, _class_id, _spawn_chance, _spawn_attempts, _strength, _initiative, _age)
{}

void Grass::draw() const
{
	cout << SYMBOL_GRASS;
}

void Grass::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Grass(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array
	world.makeEveryoneOlder();
}