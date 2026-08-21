#pragma once
#include "Location.h"
#include "Item.h"
#include <vector>
#include "Player.h"
#include"NPC.h"

class Map
{
private:
	static const int HEIGHT = 37;
	static const int WIDTH = 26;

	char baseGrid[HEIGHT][WIDTH]; // Static Layout (walls, buildings, paths)
	char activeGrid[HEIGHT][WIDTH]; // Active layout (includes dynamic obstacles and the player)

	// To store the instances of the city locations
	std::vector<Location*> locations;

	std::vector<Item*> groundItems; // Items currently lying on the ground

	std::vector<NPC*> npcs;

public:
	Map();
	~Map();

	void generateRandomObstacles(int obstacleCount);

	/* Core Logic Checks */
	bool isWalkable(int x, int y) const;
	bool isEntrance(int x, int y) const;
	char getTileAt(int x, int y) const;

	// Render the map based on the position of the player
	void displayMap(int playerX, int playerY, int viewWidth, int viewHeight, Player& player) const;

	Location* getBuildingAt(int x, int y);

	void addGroundItem(Item* item);

	// Search and remove item from ground when picked up
	Item* pickupItemAt(int playerX, int playerY);

	// Helper for map rendering
	Item* getGroundItemAt(int x, int y) const;

	void addNPC(NPC* npc);
};