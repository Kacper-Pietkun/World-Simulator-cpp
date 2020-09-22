#pragma once
#include "Plant.h"
class Sowthistle :
	public Plant
{
private:
	void spawnChild(Position child_position) const override;
	void draw() const override;
public:
	Sowthistle(World& _world, Position _position, string _class_id = NAME_SOWTHISTLE, int _spawn_chance = PERCENT_15, int _spawn_attempts = 3, int _strength = 0, int _initiative = 0, int _age = 1);
};

