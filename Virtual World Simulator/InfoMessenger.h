#pragma once
#include <iostream>

using namespace std;

class Organism;

// This class has got a string, which is updated by all functions add.. . At the end of the round string is printed to the screen, so user can see what has happened
// during the round
class InfoMessenger
{
private:
	string message;
	void resetMessage();

public:
	InfoMessenger(string start_message = "");
	void addCustomMessage(string content);
	void addNewAnimalBornedInfo(string animal_class);
	void addNewAnimalNotBornedInfo(string animal_class);
	void addNewPlantSpawnedInfo(string animal_class);
	void addNewPlantNotSpawnedInfo(string plant_class);
	void addAnimalKilledByAnimal(Organism* attacker, Organism* defender, int who_won);
	void addDefendedItslefFrom(Organism* attacker, Organism* defender);
	void addAnimalRanAway(Organism* attacker, Organism* defender, Organism* who_ran);
	void addStrengthBoost(Organism* organism, Organism* plant, int boost);
	void addPlantKillsAnimal(Organism* organism, Organism* plant);
	void addAnimalEatsPlant(Organism* animal, Organism* plant);
	void addHogweedKillsInZone(Organism* animal);
	void addAbilityActivated(bool activated);
	void printRoundRaport();
};

