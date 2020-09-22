#include <iostream>
#include "Fox.h"
#include "Constant.h"

using namespace std;

Fox::Fox(World& _world, Position _position, string _class_id, int _strength, int _initiative, int _age)
	:Animal(_world, _position, _class_id, _strength, _initiative, _age)
{}

void Fox::draw() const
{
	cout << SYMBOL_FOX;
}

void Fox::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Fox(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array			
	world.makeEveryoneOlder();
}

bool Fox::isThereStrongerOrganism(Position position) const
{
	Organism* org_at_position = world.getOrganismAt(position);
	if (org_at_position != NULL)
		return (strength < org_at_position->getStrength());
	return false;
}
