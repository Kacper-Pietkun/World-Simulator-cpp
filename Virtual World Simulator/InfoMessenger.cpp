#include "InfoMessenger.h"
#include "Organism.h"
#include <string>

InfoMessenger::InfoMessenger(string start_message)
	:message(start_message)
{}

void InfoMessenger::addCustomMessage(string content)
{
	message += content + '\n';
}

void InfoMessenger::addNewAnimalBornedInfo(string animal_class)
{
	addCustomMessage("New " + animal_class + " is borned");
}

void InfoMessenger::addNewAnimalNotBornedInfo(string animal_class)
{
	addCustomMessage("There is not enough space for a new " + animal_class + "!");
}

void InfoMessenger::addNewPlantSpawnedInfo(string plant_class)
{
	addCustomMessage("New " + plant_class + " is spawned");
}

void InfoMessenger::addNewPlantNotSpawnedInfo(string plant_class)
{
	addCustomMessage(plant_class + " could not be spawned. There is not enough space!");
}

void InfoMessenger::addAnimalKilledByAnimal(Organism* attacker, Organism* defender, int who_won)
{
	string message = "Attacker: " + attacker->getClassId() + " (strength: " + to_string(attacker->getStrength()) +
		") | Defender: " + defender->getClassId() + " (strength: " + to_string(defender->getStrength()) + ") | Winner: ";
	message += who_won == ATTACKER ? "attacker" : "defender";
	addCustomMessage(message);
}

void InfoMessenger::addDefendedItslefFrom(Organism* attacker, Organism* defender)
{
	string message = defender->getClassId() + " defended itself from being eaten by " + attacker->getClassId();
	addCustomMessage(message);
}

void InfoMessenger::addAnimalRanAway(Organism* attacker, Organism* defender, Organism* who_ran)
{
	string message = who_ran->getClassId() + " runs away from ";
	message += who_ran == attacker ? defender->getClassId() : attacker->getClassId();
	addCustomMessage(message);
}

void InfoMessenger::addStrengthBoost(Organism* organism, Organism* plant, int boost)
{
	string message = organism->getClassId() + " eats " + plant->getClassId() + " | +" + to_string(boost) + " strength!";
	addCustomMessage(message);
}

void InfoMessenger::addPlantKillsAnimal(Organism* organism, Organism* plant)
{
	string message = organism->getClassId() + " dies, after eating " + plant->getClassId();
	addCustomMessage(message);
}

void InfoMessenger::addAnimalEatsPlant(Organism* animal, Organism* plant)
{
	string message = animal->getClassId() + " eats " + plant->getClassId();
	addCustomMessage(message);
}

void InfoMessenger::addAbilityActivated(bool activated)
{
	string message = activated == true ? "SUPER POWER IS ACTIVE FOR 5 ROUNDS!" : "SUPER POWERT CANNOT BE ACTIVATED YET!";
	addCustomMessage(message);
}

void InfoMessenger::addHogweedKillsInZone(Organism* animal)
{
	string message = animal->getClassId() + " dies, because it stands to close to the hogweed";
	addCustomMessage(message);
}

void InfoMessenger::printRoundRaport()
{
	addCustomMessage(""); // adding one enter
	cout << message;
	resetMessage();
}

void InfoMessenger::resetMessage()
{
	message = "";
}