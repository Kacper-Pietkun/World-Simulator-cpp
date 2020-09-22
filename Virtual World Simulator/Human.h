#pragma once
#include "Animal.h"
#include "Constant.h"

class Human :
	public Animal
{
private:
	void draw() const override;
	int readKeyArrowInput() const override;
	int howManySteps() override;
	void activateSuperAbility() override;

public:
	Human(World& _world, Position _position, string _class_id = NAME_HUMAN, int strength = 5, int initiative = 4, int _age = 1, bool _is_ability_active = false, int _rounds_of_ability = 0);
};

