#include "Map.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Location.h"

Map::Map()
{
	// Needed to set up the map
	const std::string layout[HEIGHT] =
	{
		// Each row has 26 columns
		"**************************", // Row 1
		"*________________________*", // Row 2
		"*_####A.A##_____####S.S#_*", // Row 3
		"*_#XXXXXXX#_____#XXXXXX#_*", // Row 4
		"*_#XXXXXXX#_____#XXXXXX#_*", // Row 5
		"*_#########_____########_*", // Row 6
		"*________________________*", // Row 7
		"*________________________*", // Row 8
		"*__########_____#######__*", // Row 9
		"*__#XXXXXXG_____HXXXXX#__*", // Row 10
		"*__#XXXXXX._____.XXXXX#__*", // Row 11
		"*__#XXXXXXG_____HXXXXX#__*", // Row 12
		"*__########_____#######__*", // Row 13
		"*________________________*", // Row 14
		"*________________________*", // Row 15
		"*_####P.S##______######__*", // Row 16
		"*_#XXXXXXX#______#XXXX#__*", // Row 17
		"*_#XXXXXXX#______#XXXX#__*", // Row 18
		"*_#########______#XXXX#__*", // Row 19
		"*________________#C.C##__*", // Row 20
		"*________________________*", // Row 21
		"*______#########_________*", // Row 22
		"*______#XXXXXXX#_________*", // Row 23
		"*______#XXXXXXX#_________*", // Row 24
		"*______#XXXXXXX#_________*", // Row 25
		"*______###F.F###_________*", // Row 26
		"*________________________*", // Row 27
		"*________________________*", // Row 28
		"*_###########____________*", // Row 29
		"*_#XXXXXXXXXM____________*", // Row 30
		"*_#XXXXXXXXX.____________*", // Row 31
		"*_#XXXXXXXXXM____________*", // Row 32
		"*_###########____________*", // Row 33
		"*________________________*", // Row 34
		"*________________________*", // Row 35
		"*________________________*", // Row 36
		"********#V.V#*************"  // Row 37
	};

	// Assign all of the characters of the map
	for (int r = 0; r < HEIGHT; ++r)
	{
		for (int c = 0; c < WIDTH; ++c)
		{
			baseGrid[r][c] = layout[r][c];
			activeGrid[r][c] = layout[r][c]; // Copy the base to the active
		}
	}

	// Initialize building instances
	locations.push_back(new Location("Apartment", 'A'));
	locations.push_back(new Location("Supermarket", 'S'));
	locations.push_back(new Location("Hospital", 'H'));
	locations.push_back(new Location("Police Station", 'P'));
	locations.push_back(new Location("Gas Station", 'G'));
	locations.push_back(new Location("School", 'C'));
	locations.push_back(new Location("Safe House", 'F'));
	locations.push_back(new Location("Military Base", 'M'));
	locations.push_back(new Location("Evacuation Point", 'V'));
}

Map::~Map()
{
	for (Location* loc : locations) {
		delete loc;
	}
	locations.clear();
}

bool Map::isWalkable(int x, int y) const
{
	// Check the bounds
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		return false;
	}

	char tile = activeGrid[y][x];

	// The tiles the player are allowed to move are the following:
	// '_' Walkable street
	// '.' Building entrance door
	if (tile == '_' || tile == '.')
	{
		return true;
	}

	// Impassable tiles: '*', '#', 'X', labels ('A', 'S', etc.), and obstacles ('C', 'r', '~')
	return false;
}

bool Map::isEntrance(int x, int y) const
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return false;
	return activeGrid[y][x] == '.';
}

char Map::getTileAt(int x, int y) const
{
	return 0;
}

void Map::generateRandomObstacles(int obstacleCount)
{
	// The array of the obstacle types to be randomly placed and allocated
	char obstacleTypes[] = { 'C', 'r', '~' };
	int numTypes = sizeof(obstacleTypes) / sizeof(obstacleTypes[0]);

	int placed = 0;
	while (placed < obstacleCount)
	{
		int randY = rand() % HEIGHT;
		int randX = rand() % WIDTH;

		// Check to ensure that the tile is a street tile '_'
		if (baseGrid[randY][randX] == '_')
		{
			// Next check to ensure that it is not adjacent to an entrance to the building '.'
			bool nearDoor = false;
			for (int dy = -1; dy <= 1; ++dy)
			{
				for (int dx = -1; dx <= 1; ++dx)
				{
					int checkY = randY + dy;
					int checkX = randX + dx;

					if (checkY >= 0 && checkY < HEIGHT && checkX >= 0 && checkX < WIDTH)
					{
						if (baseGrid[checkY][checkX] == '.')
						{
							nearDoor = true;
						}
					}
				}
			}

			// If it is safe, add the obstacle into the map
			if (!nearDoor)
			{
				char chosenObstacle = obstacleTypes[rand() % numTypes];
				activeGrid[randY][randX] = chosenObstacle;
				placed++;
			}
		}
	}
}

void Map::displayMap(int playerX, int playerY, int viewWidth, int viewHeight) const
{
	// Calculate raw top-left offset
	int rawCamX = playerX - (viewWidth / 2);
	int rawCamY = playerY - (viewHeight / 2);

	// Clamp camera within map bounds
	int camX = std::clamp(rawCamX, 0, WIDTH - viewWidth);
	int camY = std::clamp(rawCamY, 0, HEIGHT - viewHeight);

	std::cout << "========================================" << std::endl;
	for (int r = camY; r < camY + viewHeight; ++r) {
		for (int c = camX; c < camX + viewWidth; ++c) {

			if (r == playerY && c == playerX) {
				std::cout << "P "; // Player character
			}
			else {
				std::cout << activeGrid[r][c] << " "; // Tile + space
			}
		}
		std::cout << std::endl;
	}
	std::cout << "========================================" << std::endl;
}

Location* Map::getBuildingAt(int x, int y)
{
	// Search the adjacent tiles to identify the building label character
	int dx[] = { 0, 0, -1, 1 };
	int dy[] = { -1, 1, 0, 0 };

	for (int i = 0; i < 4; ++i) {
		int checkX = x + dx[i];
		int checkY = y + dy[i];

		if (checkX >= 0 && checkX < WIDTH && checkY >= 0 && checkY < HEIGHT) {
			char tileLabel = activeGrid[checkY][checkX];

			// Match adjacent label symbol against registered location symbols
			for (Location* loc : locations) {
				if (loc->getSymbol() == tileLabel) {
					return loc; // Return matching building pointer
				}
			}
		}
	}

	return nullptr; // No building found adjacent to coordinates
}
