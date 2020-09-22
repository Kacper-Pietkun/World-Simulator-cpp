#pragma once
#include "Animal.h"
class Antelope :
	public Animal
{
private:
	void draw() const override;
	void spawnChild(Position child_position) const override;
	int howManySteps() override;
	bool runFromBattle() const override;

public:
	Antelope(World& _world, Position _position, string _class_id = NAME_ANTELOPE, int strength = 4, int initiative = 4, int _age = 1);
};

