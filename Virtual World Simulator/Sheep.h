#pragma once
#include "Animal.h"
#include "Constant.h"

class Sheep :
	public Animal
{
private:
	void draw() const override;
	void spawnChild(Position child_position) const override;

public:
	Sheep(World& _world, Position _position, string _class_id = NAME_SHEEP, int strength = 4, int initiative = 4, int _age = 1);
};

