#pragma once

// AUTHOR
#define AUTHOR_NAME "Kacper"
#define AUTHOR_SURNAME "Pietkun"
#define AUTHOR_INDEX 000000

// GAME DIRECTIONS
#define NUMBER_OF_DIRECTIONS 4
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT  3

// How many organisms will be spawned at the beginning og the game (SPAWN_RATE * 100% - percent of the map size)
#define SPAWN_RATE 0.3 // DECIMAL // possible values (0 - 1)
#define SPAWN_RATE_ONE_ANIMAL 0.03 // DECIMAL // possible values (0 - 1)

// Organisms
#define NUMBER_ALL_ORGANISMS 10 // It means just how many classes there are (not how many organisms are on the map) WITHOUT HUMAN
#define WOLF 0
#define SHEEP 1
#define FOX 2
#define TURTLE 3
#define ANTELOPE 4
#define GRASS 5
#define SOWTHISTLE 6
#define GUARANA 7
#define BELLADONNA 8
#define HOGWEED 9
#define HUMAN 10

// Organisms symbols
#define SYMBOL_WOLF "W"
#define SYMBOL_SHEEP "S"
#define SYMBOL_FOX "F"
#define SYMBOL_TURTLE "T"
#define SYMBOL_ANTELOPE "A"
#define SYMBOL_GRASS "G"
#define SYMBOL_SOWTHISTLE "O"
#define SYMBOL_GUARANA "N"
#define SYMBOL_BELLADONNA "B"
#define SYMBOL_HOGWEED "E"
#define SYMBOL_HUMAN "H"

// Organisms names
#define NAME_WOLF "Wolf"
#define NAME_SHEEP "Sheep"
#define NAME_FOX "Fox"
#define NAME_TURTLE "Turtle"
#define NAME_ANTELOPE "Antelope"
#define NAME_GRASS "Grass"
#define NAME_SOWTHISTLE "Sowthistle"
#define NAME_GUARANA "Guarana"
#define NAME_BELLADONNA "Belladonna"
#define NAME_HOGWEED "Hogweed"
#define NAME_HUMAN "Human"

// Collision
#define ATTACKER 1
#define DEFENDER 0

// Table which tells us what the order of action is
// It has some length and it is resized if ther is too many organisms
#define TABLE_ACTION_SIZE 50



// Random numbers
#define PERCENT_100 100
#define PERCENT_75 75
#define PERCENT_50 50
#define PERCENT_25 25
#define PERCENT_15 15
#define PERCENT_10 10
#define PERCENT_5 5


// Collision result
#define STOP 0
#define CAN_GO_FURTHER 1


// For random numbers
#define X 0
#define Y 1

#define IS_RANDOM -1


// Keys mapping
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER '\r'
#define KEY_SUPER_ABILITY 'a'
#define KEY_SAVE_GAME 's'
#define KEY_LOAD_GAME 'l'
#define KEY_QUIT_GAME 'q'



// SAVE AND LOAD FILE
#define FILE_GAME "game.txt"

// For letting know that a new game has been created or the game has been ended
#define NEW_GAME 111
#define END_GAME -111
#define CONTINUE 0