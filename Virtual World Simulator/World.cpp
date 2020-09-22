#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "World.h"
#include "Constant.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Grass.h"
#include "Sowthistle.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "Hogweed.h"
#include "Human.h"

using namespace std;

World::World(int _size_width, int _size_height)
	: size_width(_size_width), size_height(_size_height), info_messenger(), key_input(KEY_ENTER), key_ability_active(false)
{
	priority_action = new PriorityAction();
	organisms = new Organism * *[_size_height]; // Allocating memory for world's "board"
	for (int i = 0; i < _size_height; i++)
	{
		organisms[i] = new Organism * [_size_width];
		for (int j = 0; j < _size_width; j++)
			organisms[i][j] = NULL;
	}
}

World::~World()
{
	for (int i = 0; i < size_height; i++)
	{
		for (int j = 0; j < size_width; j++)
		{
			if (organisms[i][j] != NULL)
				delete organisms[i][j];
		}
		delete organisms[i];
	}
	delete[] organisms;
	delete priority_action;
}

void World::saveGame()
{
	fstream file;
	string organism_info; // TEMPLATE: CLASS_ID POSITION(x,y) STRENGTH INITIATIVE AGE ACTIVE_ABILITY ACTIVE_ABILITY_ROUNDS (for organisms that are not human last two properties may be anything (we won't look at it))
	file.open(FILE_GAME, ios::out);

	file << size_height << " " << size_width << endl;
	for (int i = 0; i < size_height; i++)
	{
		for (int j = 0; j < size_width; j++)
		{
			if (organisms[i][j] != NULL)
			{
				organism_info = organisms[i][j]->getClassId() + " " + to_string(organisms[i][j]->getPosition().getX()) + " " +
					to_string(organisms[i][j]->getPosition().getY()) + " " + to_string(organisms[i][j]->getStrength()) + " " +
					to_string(organisms[i][j]->getInitiative()) + " " + to_string(organisms[i][j]->getAge()) + " " +
					to_string(organisms[i][j]->getIsAbilityActive()) + " " + to_string(organisms[i][j]->getRoundsOfAbility());
				file << organism_info << endl;
			}
		}
	}
	info_messenger.addCustomMessage("Game has been saved!");
	info_messenger.printRoundRaport();

	file.close();
}

void World::deleteCurrentWorld()
{
	for (int i = 0; i < size_height; i++)
		for (int j = 0; j < size_width; j++)
			if (organisms[i][j] != NULL)
			{
				priority_action->getOrganismsToKill().push(organisms[i][j]);
				organisms[i][j] = NULL;
			}
	priority_action->deleteOrganismsFromStack(); // deallocating memory from priority action
	this->~World(); // deallocating organisms map
}

void World::allocateNewWorld(int width, int height)
{
	priority_action = new PriorityAction();
	organisms = new Organism * *[height]; // Allocating memory for world's "board"
	for (int i = 0; i < height; i++)
	{
		organisms[i] = new Organism * [width];
		for (int j = 0; j < width; j++)
			organisms[i][j] = NULL;
	}
}

void World::loadGame()
{
	deleteCurrentWorld();

	string s_height, s_width, s_class_id, s_pos_x, s_pos_y, s_strength, s_initiative, s_age, s_active_ability, s_ability_rounds;
	int height, width, pos_x, pos_y, strength, initiative, age, active_ability, ability_rounds;

	fstream file;
	file.open(FILE_GAME, ios::in);

	if (file.good() == true)
	{

		file >> s_height >> s_width;
		height = atoi(s_height.c_str());
		width = atoi(s_width.c_str());
		allocateNewWorld(width, height);
		size_width = width;
		size_height = height;

		while (file.eof() == false) // Loop thorugh all the organisms and create them
		{
			file >> s_class_id >> s_pos_x >> s_pos_y >> s_strength >> s_initiative >> s_age >> s_active_ability >> s_ability_rounds;
			pos_x = atoi(s_pos_x.c_str());
			pos_y = atoi(s_pos_y.c_str());
			strength = atoi(s_strength.c_str());
			initiative = atoi(s_initiative.c_str());
			age = atoi(s_age.c_str());
			active_ability = atoi(s_active_ability.c_str());
			ability_rounds = atoi(s_ability_rounds.c_str());

			if (s_class_id == NAME_WOLF)
				organisms[pos_y][pos_x] = new Wolf(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_SHEEP)
				organisms[pos_y][pos_x] = new Sheep(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_FOX)
				organisms[pos_y][pos_x] = new Fox(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_TURTLE)
				organisms[pos_y][pos_x] = new Turtle(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_ANTELOPE)
				organisms[pos_y][pos_x] = new Antelope(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_GRASS)
				organisms[pos_y][pos_x] = new Grass(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_SOWTHISTLE)
				organisms[pos_y][pos_x] = new Sowthistle(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_GUARANA)
				organisms[pos_y][pos_x] = new Guarana(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_BELLADONNA)
				organisms[pos_y][pos_x] = new Belladonna(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_HOGWEED)
				organisms[pos_y][pos_x] = new Hogweed(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age);
			else if (s_class_id == NAME_HUMAN)
				organisms[pos_y][pos_x] = new Human(*this, Position(pos_x, pos_y), s_class_id, strength, initiative, age, active_ability, ability_rounds);
			priority_action->getOrganismsToSpawn().push(organisms[pos_y][pos_x]);
		}
		file.close();
	}
	priority_action->spawnOrganismsFromStack();
}

void World::startGame(bool loaded)
{
	int choice;
	if (loaded == false)
		spawnOnStart();
	do
	{
		drawWorld();
		info_messenger.printRoundRaport();
		choice = userClickButton();
		if (choice == NEW_GAME || choice == END_GAME) break;
		system("cls");
		executeRound();
	} while (true);

	if (choice == NEW_GAME)
	{
		system("cls");
		info_messenger.addCustomMessage("Game has been loaded!");
		info_messenger.printRoundRaport();
		startGame(true);
	}
}

void World::spawnOnStart()
{
	Position position;
	int number_of_organisms = SPAWN_RATE * size_width * size_height + 1;
	int number_of_one_organism = SPAWN_RATE_ONE_ANIMAL * size_width * size_height; // We know that every organism will spawn
	int which_organism = 0;
	for (int i = 0; i < number_of_organisms; i++)
	{
		do
		{
			position = generatePosition();
		} while (isThisSpotFree(position) == false);
		if (i == 0) // Spawn human at the beginning
			organisms[position.getY()][position.getX()] = new Human(*this, position);
		else if (which_organism < 10 && number_of_one_organism > 0)
			organisms[position.getY()][position.getX()] = createRandomOrganism(position, which_organism);
		else
			organisms[position.getY()][position.getX()] = createRandomOrganism(position, IS_RANDOM);
		priority_action->getOrganismsToSpawn().push(organisms[position.getY()][position.getX()]);
		makeEveryoneOlder();
		if (i != 0 && number_of_one_organism > 0 && i % number_of_one_organism == 0)
			which_organism++;
	}
	priority_action->spawnOrganismsFromStack();
}

Organism* World::createRandomOrganism(Position position, int is_random)
{
	int random = is_random == IS_RANDOM ? rand() % NUMBER_ALL_ORGANISMS : is_random;
	switch (random)
	{
	case WOLF:
		return new Wolf(*this, position);
	case SHEEP:
		return new Sheep(*this, position);
	case FOX:
		return new Fox(*this, position);
	case TURTLE:
		return new Turtle(*this, position);
	case ANTELOPE:
		return new Antelope(*this, position);
	case GRASS:
		return new Grass(*this, position);
	case SOWTHISTLE:
		return new Sowthistle(*this, position);
	case GUARANA:
		return new Guarana(*this, position);
	case BELLADONNA:
		return new Belladonna(*this, position);
	case HOGWEED:
		return new Hogweed(*this, position);
	}
	return NULL;
}

void World::executeRound() const
{
	int action_length = priority_action->getLength();

	Organism* organism;
	for (int i = 0; i < action_length; i++)
	{
		organism = priority_action->getOrganismAtPos(i);
		if (priority_action->isOrganismDead(organism) == false)
			priority_action->getOrganismAtPos(i)->action(); // If an organisnm will be killed in action then we don't remove it from priority action array (otherwise ACCESS VIOLATION)
	}

	priority_action->spawnOrganismsFromStack(); // We have to spawn from stack before deleting from stack to avoid errors
	priority_action->deleteOrganismsFromStack();
}

void World::drawWorld() const
{
	cout << AUTHOR_NAME << " " << AUTHOR_SURNAME << " " << AUTHOR_INDEX << endl;
	cout << "1. Click arrows to move around or enter to skip moving!" << endl;
	cout << "2. Click \"a\" to use your super ability (antelope speed)!" << endl;
	cout << "3. Click \"s\" to save game to file" << endl;
	cout << "4. Click \"l\" to load game from file" << endl;
	cout << "5. Click \"q\" to quit game" << endl << endl;
	for (int i = 0; i < size_height; i++)
	{
		for (int j = 0; j < size_width; j++)
		{
			if (organisms[i][j] == NULL)
				cout << ".";
			else
				organisms[i][j]->draw();

		}
		for (int k = 0; k < 10; k++)
			cout << " ";
		cout << getWorldLegend(i) << endl;
	}
	drawWorldLegend(size_height);
	cout << endl;
}

void World::drawWorldLegend(int start_row) const
{
	for (int i = start_row; i < NUMBER_ALL_ORGANISMS + 1; i++)
	{
		for (int j = 0; j < size_width + 10; j++)
			cout << " ";
		cout << getWorldLegend(i) << endl;
	}
}

string World::getWorldLegend(int row) const
{
	if (row == 0)
		return "MAP LEGEND:";
	else if (row == WOLF + 1)
		return "W - WOLF";
	else if (row == SHEEP + 1)
		return "S - SHEEP";
	else if (row == FOX + 1)
		return "F - FOX";
	else if (row == TURTLE + 1)
		return "T - TURTLE";
	else if (row == ANTELOPE + 1)
		return "A - ANTELOPE";
	else if (row == GRASS + 1)
		return "G - GRASS";
	else if (row == SOWTHISTLE + 1)
		return "O - SOWTHISTLE";
	else if (row == GUARANA + 1)
		return "N - GUARANA";
	else if (row == BELLADONNA + 1)
		return "B - BELLADONNA";
	else if (row == HOGWEED + 1)
		return "E - HOGWEED";
	else if (row == HUMAN + 1)
		return "H - HUMAN";
	return "";
}

void World::makeEveryoneOlder() const
{
	for (int i = 0; i < size_height; i++)
	{
		for (int j = 0; j < size_width; j++)
		{
			if (organisms[i][j] != NULL)
				organisms[i][j]->setAge(organisms[i][j]->getAge() + 1);
		}
	}
}

Position World::generatePosition() const
{
	int x = rand() % size_width;
	int y = rand() % size_height;
	Position new_pos(x, y);
	return new_pos;
}

void World::changeOrganismPosition(Organism* org, Position old_position, Position new_position)
{
	Organism* organism = getOrganismAt(old_position);
	if (org == organism) // validation
	{
		organism->setPosition(new_position);
		organisms[new_position.getY()][new_position.getX()] = organism;
		organisms[old_position.getY()][old_position.getX()] = NULL;
	}
}

void World::setOrganismPosition(Position position, Organism* org)
{
	org->setPosition(position);
	organisms[position.getY()][position.getX()] = org;
}

void World::killOrganismAt(Position position)
{
	if (isThisSpotInsideMap(position) == true && isThisSpotFree(position) == false) // validation of the position
	{
		priority_action->getOrganismsToKill().push(getOrganismAt(position)); // we don't delete organism now (in priority action array), because we don't want to mess up priority action array during iterating it 
																			 // instead we add organisms to kill to stack and delete them after round it finished
		// delete organisms[position.getY()][position.getX()]; WE DONT WANT DELETE HERE ORGANISM BEACUSE THERE IS A POINTER TO THIS ORGANISM AT STACK IN PRIORITY ACTION, IT WILL BE DELETED THERE
		organisms[position.getY()][position.getX()] = NULL;
	}
}

int World::userClickButton()
{
	char choice;
	do
	{
		choice = _getch();
		switch (choice)
		{
		case KEY_DOWN:
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_UP:
		case KEY_ENTER:
			key_input = choice;
			return CONTINUE;
		case KEY_SUPER_ABILITY:
			key_ability_active = true;
			info_messenger.addCustomMessage("You clicked a button to activate ability!");
			info_messenger.printRoundRaport();
			break;
		case KEY_SAVE_GAME:
			saveGame();
			break;
		case KEY_LOAD_GAME:
			loadGame();
			return NEW_GAME;
		case KEY_QUIT_GAME:
			return END_GAME;
		}
	} while (true);

	return NULL;
}

bool World::isThisSpotFree(Position position) const
{
	return (organisms[position.getY()][position.getX()] == NULL);
}

bool World::isThisSpotInsideMap(Position position) const
{
	int x = position.getX();
	int y = position.getY();
	return (x >= 0 && x < size_width&& y >= 0 && y < size_height);
}

int World::getSizeWidth() const
{
	return size_width;
}

int World::getSizeHeight() const
{
	return size_height;
}

PriorityAction* World::getPriorityAction() const
{
	return priority_action;
}

InfoMessenger& World::getInfoMessenger()
{
	return info_messenger;
}

Organism* World::getOrganismAt(Position pos) const
{
	if (organisms[pos.getY()][pos.getX()] != NULL)
		return organisms[pos.getY()][pos.getX()];
	return NULL;
}

int World::getKeyInput() const
{
	return key_input;
}

bool World::getKeyAbilityActiveInput() const
{
	return key_ability_active;
}

void World::setKeyActiveAbility(bool value)
{
	key_ability_active = value;
}