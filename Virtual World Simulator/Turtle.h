#pragma once
#include "Animal.h"
#include "Constant.h"
class Turtle :
	public Animal
{
private:
	void draw() const override;
	void spawnChild(Position child_position) const override;
	bool isItAbleToMove() const override;
	bool defendItself(Organism* attacker) const override;

public:
	Turtle(World& _world, Position _position, string _class_id = NAME_TURTLE, int strength = 2, int initiative = 1, int _age = 1);
};
