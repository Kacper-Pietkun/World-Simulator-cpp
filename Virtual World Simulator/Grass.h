#pragma once
#include "Plant.h"
#include "Constant.h"

class Grass :
	public Plant
{
private:
	void spawnChild(Position child_position) const override;
	void draw() const override;
public:
	Grass(World& _world, Position _position, string _class_id = NAME_GRASS, int _spawn_chance = PERCENT_25, int _spawn_attempts = 1, int _strength = 0, int _initiative = 0, int _age = 1);
};

