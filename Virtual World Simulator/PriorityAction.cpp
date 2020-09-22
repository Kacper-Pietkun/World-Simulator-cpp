#include "PriorityAction.h"
#include <iostream>

PriorityAction::PriorityAction()
	: max_size(TABLE_ACTION_SIZE), actual_size(0)
{
	priority_actions = new Organism * [TABLE_ACTION_SIZE];
	for (int i = 0; i < TABLE_ACTION_SIZE; i++)
		priority_actions[i] = NULL;
}

PriorityAction::~PriorityAction()
{
	delete[] priority_actions;
}

void PriorityAction::addToPriorityActions(Organism* org)
{
	if (actual_size == max_size)
		priority_actions = reallocateMemory(max_size / TABLE_ACTION_SIZE);
	priority_actions[actual_size] = org;
	actual_size++;

	// insert organism on adequate position according to its initiative or age
	int i = actual_size - 2;
	while (i >= 0 && (priority_actions[i]->getInitiative() < org->getInitiative() ||
		(priority_actions[i]->getInitiative() == org->getInitiative() && priority_actions[i]->getAge() < org->getAge())))
	{
		priority_actions[i + 1] = priority_actions[i];
		i--;
	}
	priority_actions[i + 1] = org;
}

int PriorityAction::indexOfThatOrganism(Organism* org) const
{
	for (int i = 0; i < actual_size; i++)
	{
		if (priority_actions[i] == org)
			return i;
	}
	return -1;
}

void PriorityAction::deleteFromActions(Organism* org)
{
	int index = indexOfThatOrganism(org);
	if (index == -1)
		return;

	actual_size--;
	for (int i = index; i < actual_size; i++)
		priority_actions[i] = priority_actions[i + 1];
}

void PriorityAction::deleteOrganismsFromStack()
{
	Organism* org_to_kill = NULL;
	while (organisms_to_kill.peek() != NULL)
	{
		org_to_kill = organisms_to_kill.peek();
		deleteFromActions(org_to_kill); // It only moves pointers in array it doesn't deallocate memory
		delete org_to_kill; // We have to deallocate it here
		organisms_to_kill.pop();
	}
}

void PriorityAction::spawnOrganismsFromStack()
{
	Organism* org_to_spawn = NULL;
	while (organisms_to_spawn.peek() != NULL)
	{
		org_to_spawn = organisms_to_spawn.peek();
		addToPriorityActions(org_to_spawn);
		organisms_to_spawn.pop();
	}
}

bool PriorityAction::isOrganismDead(Organism* org) const
{
	return organisms_to_kill.foundInStack(org);
}

Organism** PriorityAction::reallocateMemory(int multiplier)
{
	max_size = TABLE_ACTION_SIZE * (multiplier + 1);
	Organism** temp_arr = new Organism * [max_size];
	for (int i = 0; i < max_size; i++)
	{
		if (i < actual_size)
			temp_arr[i] = priority_actions[i];
		else
			temp_arr[i] = NULL;
	}
	delete[] priority_actions;
	return temp_arr;
}

Organism* PriorityAction::getOrganismAtPos(int pos) const
{
	return priority_actions[pos];
}

Stack& PriorityAction::getOrganismsToKill()
{
	return organisms_to_kill;
}

Stack& PriorityAction::getOrganismsToSpawn()
{
	return organisms_to_spawn;
}

int PriorityAction::getLength() const
{
	return actual_size;
}
