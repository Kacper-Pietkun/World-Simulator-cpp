#pragma once
#include "Organism.h"
#include "Constant.h"
#include "Stack.h"

class Organism;

class PriorityAction
{
private:
	int max_size, actual_size;
	Organism** priority_actions;
	Stack organisms_to_kill; // Contains all organisms that will be killed at the end of the round // WE NEED THIS TWO STACKS to do things after iterating over array triggering actions
	Stack organisms_to_spawn; // Contains all organisms that will born at the end of the round       

	Organism** reallocateMemory(int multiplier);
	int indexOfThatOrganism(Organism* org) const; // Index in the table, if it doesn't find this organism it returns -1
	void deleteFromActions(Organism* org); // Delete single organism from array
	void addToPriorityActions(Organism* org); // Add single organism to array

public:
	PriorityAction();
	~PriorityAction();

	void deleteOrganismsFromStack(); // Kills organisms that are at the stack
	void spawnOrganismsFromStack(); // Spawn organisms that are at the stack
	bool isOrganismDead(Organism* org) const; // Check if another organism has not already killed this organism in this round
	Organism* getOrganismAtPos(int pos) const; // we know it will return valid organism
	Stack& getOrganismsToKill();
	Stack& getOrganismsToSpawn();
	int getLength() const;
};

