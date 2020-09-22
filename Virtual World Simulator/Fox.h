#pragma once
#include "Animal.h"
class Fox :
	public Animal
{
private:
	void draw() const override;
	void spawnChild(Position child_position) const override;
	bool isThereStrongerOrganism(Position position) const override;

public:
	Fox(World& _world, Position _position, string _class_id = NAME_FOX, int strength = 3, int initiative = 7, int _age = 1);
};

