#include <iostream>
#include "Antelope.h"
#include "Constant.h"

using namespace std;

Antelope::Antelope(World& _world, Position _position, string _class_id, int _strength, int _initiative, int _age)
	:Animal(_world, _position, _class_id, _strength, _initiative, _age)
{}

void Antelope::draw() const
{
	cout << SYMBOL_ANTELOPE;
}

void Antelope::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Antelope(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array
	world.makeEveryoneOlder();
}

int Antelope::howManySteps()
{
	return rand() % 2 + 1;
}

bool Antelope::runFromBattle() const
{
	int number_of_places = howManyNotBusyPlaces();
	return (rand() % 2 == 0 && number_of_places > 0); // 50% chance to run
}

