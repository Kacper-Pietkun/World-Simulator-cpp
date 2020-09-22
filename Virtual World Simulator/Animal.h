#pragma once
#include "Organism.h"
class Animal :
	public Organism
{
private:
	Position getPositionToMove(int direction, int how_many_steps) const; // returns new position where animal will go (it returns occupied spots and free spots) (it doesn't return spots outside of the map)
	int numberOfAccessiblePositions(int how_many_steps) const; // returns number of accessible positions where animal can go (for exampe for fox it doesn't count positions where are  stronger organisms)
	Position getRandomPositionToGo(int how_many_steps) const;
	Position getPositionForHumanToGo(int how_many_steps) const;
	virtual void activateSuperAbility();
protected:
	virtual bool collision(Organism* collision_organism) override; // Handling contact with another organism // bool return (true if organism can go further if they are going more than one step, false if they must stop)

	// Organisms abilities
	virtual bool isThereStrongerOrganism(Position position) const; // Implementation in this calss will alway return false, because this ability is only for fox
	virtual bool isItAbleToMove() const; // Implementation in this calss will alway return true, For Turtle 25% chance to move
	virtual int howManySteps(); // Implementation in this calss will always return 1, Antelope will generate 1 or 2
	virtual bool defendItself(Organism* attacker) const; // Implementation in this calss will alway return false, Turtle can defend himsel if attacker strength is less than 5
	virtual bool runFromBattle() const;

	virtual int readKeyArrowInput() const;
	virtual void draw() const = 0; // Prints symbol adequate for class
	void action() override; // For instace moving
	virtual void spawnChild(Position child_position) const; // If there is a place spawns child

public:
	Animal(World& _world, Position _position, string _class_id, int _strength, int _initiative, int _age, bool _is_ability_active = false, int _rounds_of_ability = 0);
};

