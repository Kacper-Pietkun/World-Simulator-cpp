#pragma once
#include "Plant.h"
class Hogweed :
	public Plant
{
private:
	void spawnChild(Position child_position) const override;
	bool collision(Organism* attacker) override;
	void killAllNearbyAnimals() override;
	void draw() const override;
public:
	Hogweed(World& _world, Position _position, string _class_id = NAME_HOGWEED, int _spawn_chance = PERCENT_5, int _spawn_attempts = 1, int _strength = 10, int _initiative = 0, int _age = 1);
};

