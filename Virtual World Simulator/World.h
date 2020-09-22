#pragma once
#include "PriorityAction.h"
#include "Organism.h"
#include "Position.h"
#include "InfoMessenger.h"

class PriorityAction;
class Organism;

class World
{
private:
	bool key_ability_active;
	int key_input;
	int size_width;
	int size_height;
	Organism*** organisms; // we want 2D array of pointers
	PriorityAction* priority_action; // In this array first are organisms with bigger initiative (or age if initiative is equal)
	InfoMessenger info_messenger;

	Position generatePosition() const; // generate psoition which coordinates fit size of the map
	void spawnOnStart(); // Triggered only once at the beginning, spawns organisms
	void executeRound() const; // Triggered at the beginning of each round // Makes organisms do action()
	void drawWorld() const; // draws everuthing after round was executed // Only map and author credits, not game information
	int userClickButton();
	Organism* createRandomOrganism(Position position, int is_random);
	string getWorldLegend(int row) const; // returns row of the map legend
	void drawWorldLegend(int start_row) const; // prints legend what symbol is what organism
	void saveGame();
	void loadGame();
	void deleteCurrentWorld(); // after calling to load game
	void allocateNewWorld(int width, int height); // after calling to load game
public:
	World(int _size_width, int _size_height);
	~World();

	void startGame(bool loaded);
	void makeEveryoneOlder() const; // For every organism on the map age is increased (triggered when new organism is created for instace breeding or spawn on start)
	void changeOrganismPosition(Organism* org, Position old_position, Position new_position);
	void setOrganismPosition(Position position, Organism* org);
	void killOrganismAt(Position position);

	PriorityAction* getPriorityAction() const;
	InfoMessenger& getInfoMessenger();
	Organism* getOrganismAt(Position pos) const;
	bool isThisSpotFree(Position position) const; // checks if there isn't any organism on that spot
	bool isThisSpotInsideMap(Position position) const; // Checks if position is not outside of the map
	int getSizeWidth() const;
	int getSizeHeight() const;
	int getKeyInput() const;
	bool getKeyAbilityActiveInput() const;
	void setKeyActiveAbility(bool value);
};

