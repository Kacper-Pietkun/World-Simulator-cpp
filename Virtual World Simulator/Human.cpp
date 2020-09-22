#include <iostream>
#include "Human.h"
#include "Constant.h"

using namespace std;

Human::Human(World& _world, Position _position, string _class_id, int _strength, int _initiative, int _age, bool _is_ability_active, int _rounds_of_ability)
	:Animal(_world, _position, _class_id, _strength, _initiative, _age, _is_ability_active, _rounds_of_ability)
{ }

void Human::draw() const
{
	cout << SYMBOL_HUMAN;
}

int Human::readKeyArrowInput() const
{
	return world.getKeyInput();
}

int Human::howManySteps()
{
	rounds_of_ability++;
	if (is_ability_active == true)
	{

		if (rounds_of_ability <= 3)
			return 2;
		else if (rounds_of_ability <= 5)
			return rand() % 2 + 1;
		else if (rounds_of_ability == 10)
			is_ability_active = false; // Changing active to false after 10 round because, if it is inactive then we know that player can use it again
	}
	return 1;
}

void Human::activateSuperAbility()
{
	InfoMessenger& info_messenger = world.getInfoMessenger();
	if (is_ability_active == false)
	{
		is_ability_active = true;
		rounds_of_ability = 0;
		info_messenger.addAbilityActivated(true);
	}
	else
		info_messenger.addAbilityActivated(false);
}
