#pragma once
#include "Plant.h"
#include "Constant.h"

class Belladonna :
	public Plant
{
private:
	void spawnChild(Position child_position) const override;
	bool collision(Organism* attacker) override;
	void draw() const override;
public:
	Belladonna(World& _world, Position _position, string _class_id = NAME_BELLADONNA, int _spawn_chance = PERCENT_10, int _spawn_attempts = 1, int _strength = 99, int _initiative = 0, int _age = 1);
};

