#include <iostream>
#include "Sheep.h"
#include "Constant.h"

using namespace std;

Sheep::Sheep(World& _world, Position _position, string _class_id, int _strength, int _initiative, int _age)
	:Animal(_world, _position, _class_id, _strength, _initiative, _age)
{}

void Sheep::draw() const
{
	cout << SYMBOL_SHEEP;
}

void Sheep::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Sheep(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array
	world.makeEveryoneOlder();
}