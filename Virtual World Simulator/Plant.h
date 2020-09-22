#pragma once
#include "Organism.h"
class Plant :
	public Organism
{
private:
	virtual void killAllNearbyAnimals();
protected:
	int spawn_chance;
	int spawn_attempts;
	virtual void spawnChild(Position child_position) const = 0; // If there is a place spawns child
	void action() override; // For spreading other plants
	virtual void draw() const = 0; // Prints symbol adequate for class

public:
	Plant(World& _world, Position _position, string _class_id, int _spawn_chance, int _spawn_attempts, int _strength, int _initiative, int _age);
	virtual bool collision(Organism* collision_organism) override; // Handling contact with another organism // bool return (true if organism is killed after eating it, false if not)
};

