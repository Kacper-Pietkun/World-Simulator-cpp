#include <iostream>
#include <time.h>
#include "World.h"
#include "Wolf.h"

using namespace std;

int main()
{
	srand(time(NULL));
	int map_width, map_height;
	cout << AUTHOR_NAME << " " << AUTHOR_SURNAME << " " << AUTHOR_INDEX << endl;
	cout << "Type height of the map: ";
	cin >> map_height;
	cout << "Type width of the map: ";
	cin >> map_width;
	system("cls");

	World world(map_width, map_height);
	world.startGame(false);

	return 0;
}
