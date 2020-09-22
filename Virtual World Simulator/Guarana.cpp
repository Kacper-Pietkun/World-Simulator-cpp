#include <iostream>
#include "Guarana.h"
#include "Constant.h"

using namespace std;

Guarana::Guarana(World& _world, Position _position, string _class_id, int _spawn_chance, int _spawn_attempts, int _strength, int _initiative, int _age, int _strength_boost)
	:Plant(_world, _position, _class_id, _spawn_chance, _spawn_attempts, _strength, _initiative, _age)
{
	strength_boost = _strength_boost;
}

void Guarana::draw() const
{
	cout << SYMBOL_GUARANA;
}

void Guarana::spawnChild(Position child_position) const
{
	world.setOrganismPosition(child_position, new Guarana(world, child_position));
	world.getPriorityAction()->getOrganismsToSpawn().push(world.getOrganismAt(child_position)); // We push it to stack, because it will add every spawned in this round organism to array
																								// at the end of the round, so ew don't cause any troubles while iterating array
	world.makeEveryoneOlder();
}

bool Guarana::collision(Organism* attacker)
{
	InfoMessenger& info_messenger = world.getInfoMessenger(); // get reference to information messenger to add information to round raport 
	info_messenger.addStrengthBoost(attacker, this, strength_boost);
	attacker->setStrength(attacker->getStrength() + strength_boost);
	return false;
}


