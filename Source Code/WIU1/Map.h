#pragma once
#include <vector>
#include <string>
#include "Location.h"
#include "Item.h"
#include "Player.h"
#include "NPC.h"
#include "Zombie.h"

class Map
{
private:
	static const int HEIGHT = 40;
	static const int WIDTH = 41;

	char baseGrid[HEIGHT][WIDTH]; // Static Layout (walls, buildings, paths)
	char activeGrid[HEIGHT][WIDTH]; // Active layout (includes dynamic obstacles and the player)

	// To store the instances of the city locations
	std::vector<Location*> locations;

	std::vector<Item*> groundItems; // Items currently lying on the ground

	std::vector<NPC*> npcs;

	std::vector<Zombie*> zombies; // The enemies to kill

public:
	Map();
	~Map();

	void generateRandomLayout(int obstacleCount, int itemCount);
	void spawnRandomZombies(int zombieCount);
	void randomizeAllLocationLayouts(int furnitureCount = 5, int itemCount = 4);

	void updateZombies(int playerX, int playerY);
	void removeZombie(Zombie* target);

	/* Core Logic Checks */
	bool isWalkable(int x, int y) const;
	bool isEntrance(int x, int y) const;
	char getTileAt(int x, int y) const;

	

	// Render the map based on the position of the player
	void displayMap(int playerX, int playerY, int viewWidth, int viewHeight, Player& player) const;
	Location* getBuildingAt(int x, int y);

	void addGroundItem(Item* item);
	Item* pickupItemAt(int playerX, int playerY); // Search and remove item from ground when picked up
	Item* getGroundItemAt(int x, int y) const; // Helper for map rendering
	Location* getLocationByName(std::string name);
	Zombie* getZombieAt(int x, int y) const;
};