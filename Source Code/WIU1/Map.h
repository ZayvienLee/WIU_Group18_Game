#pragma once
#include "Location.h"
#include <vector>

class Map
{
private:
	static const int HEIGHT = 37;
	static const int WIDTH = 26;

	char baseGrid[HEIGHT][WIDTH]; // Static Layout (walls, buildings, paths)
	char activeGrid[HEIGHT][WIDTH]; // Active layout (includes dynamic obstacles and the player)

	// To store the instances of the city locations
	std::vector<Location*> locations;

public:
	Map();
	~Map();

	void generateRandomObstacles(int obstacleCount);

	/* Core Logic Checks */
	bool isWalkable(int x, int y) const;
	bool isEntrance(int x, int y) const;
	char getTileAt(int x, int y) const;

	// Render the map based on the position of the player
	void displayMap(int playerX, int playerY, int viewWidth = 15, int viewHeight = 15) const;

	Location* getBuildingAt(int x, int y);
};