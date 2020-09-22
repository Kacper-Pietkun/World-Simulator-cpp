#pragma once
#include "Animal.h"
#include "Constant.h"
class Wolf :
	public Animal
{
private:
	void spawnChild(Position child_position) const override;
	void draw() const override;

public:
	Wolf(World& _world, Position _position, string _class_id = NAME_WOLF, int strength = 9, int initiative = 5, int _age = 1);
};

