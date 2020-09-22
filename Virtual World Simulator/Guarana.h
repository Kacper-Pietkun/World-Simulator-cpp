#pragma once
#include "Plant.h"
#include "Constant.h"

class Guarana :
	public Plant
{
private:
	int strength_boost;
	void spawnChild(Position child_position) const override;
	bool collision(Organism* attacker) override;
	void draw() const override;
public:
	Guarana(World& _world, Position _position, string _class_id = NAME_GUARANA, int _spawn_chance = PERCENT_10,
		int _spawn_attempts = 1, int _strength = 0, int _initiative = 0, int _age = 1, int _strength_boost = 3);
};

