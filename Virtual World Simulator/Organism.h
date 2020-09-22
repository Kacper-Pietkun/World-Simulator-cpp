#pragma once
#include "World.h"
#include "Position.h"

using namespace std;

class World;

class Organism
{
protected:
	string class_id; // For comparing classes
	int age;
	int strength;
	int initiative;
	World& world;
	Position position;
	bool is_ability_active; // for human // but we need it here to be able to save it to txt file
	int rounds_of_ability; // Turned on or off, it depends

	virtual bool collision(Organism* collision_organism) = 0; // Handling contact with another organism
	int howManyNotBusyPlaces() const; // How many not occupied spots there is nearby this organism // Looks for four spots (up, down, left, right)

public:
	Organism(World& _world, Position _position, string _class_id, int strength, int initiative, int _age, bool _is_ability_active = false, int _rounds_of_ability = 0);
	virtual void action() = 0; // For instace moving
	virtual void draw() const = 0; // Prints symbol adequate for class
	virtual void spawnChild(Position child_position) const = 0; // If there is a place spawns child


	Position getNotBusyPlace() const; // Returns one of the free spots nearby this organism (if there are such places) // Looks for eight spots (also diagonally)
	int getAge() const;
	void setAge(int age);
	int getInitiative() const;
	int getStrength() const;
	void setStrength(int _strength);
	string getClassId() const;
	Position getPosition() const;
	void setPosition(Position pos);
	bool getIsAbilityActive() const;
	int getRoundsOfAbility() const;
};

