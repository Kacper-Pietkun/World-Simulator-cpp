#include <iostream>
#include "Turtle.h"
#include "Constant.h"

using namespace std;

Turtle::Turtle(World& _world, Position _position, string _class_id, int _strength, int _initiative, int _age)
	:Animal(_world, _position, _class_id, _strength, _initiative, _age)
{}

void Turtle::draw() const
{
	cout << SYMBOL_TURTLE;
}

void Turtle::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Turtle(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array			
	world.makeEveryoneOlder();
}

bool Turtle::isItAbleToMove() const
{
	int will_move = rand() % PERCENT_100; // 0 - 99
	return (will_move < PERCENT_25); // 0 - 24
}

bool Turtle::defendItself(Organism* attacker) const
{
	return (attacker->getStrength() < 5);
}