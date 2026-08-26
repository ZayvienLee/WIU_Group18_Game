#include <string>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <random>

#include "Map.h"
#include "Location.h"
#include "Item.h"
#include "Food.h"
#include "Water.h"
#include "Medicine.h"
#include "Player.h"
#include "Zombie.h"
#include "Ammunition.h"

Map::Map()
{
	// Needed to set up the map
	const std::string layout[HEIGHT] =
	{
		// Each row has 41 columns
		"*****************************************", // Row 1
		"*_________________#####_________________*", // Row 2
		"*_________________#XXX#_________________*", // Row 3
		"*_________________#XXX#_________________*", // Row 4
		"*_________________#A.A#_________________*", // Row 5
		"*___________________________####S.S####_*", // Row 6
		"*___________________________#XXXXXXXXX#_*", // Row 7
		"*_#########_________________#XXXXXXXXX#_*", // Row 8
		"*_#XXXXXXX#_________________#XXXXXXXXX#_*", // Row 9
		"*_#XXXXXXX#_________________#XXXXXXXXX#_*", // Row 10
		"*_#XXXXXXX#_________________###########_*", // Row 11
		"*_#XXXXXXX#_____________________________*", // Row 12
		"*_###XXX###__________________#########__*", // Row 13
		"*___#C.C#____________________#XXXXXXX#__*", // Row 14
		"*____________________________#XXXXXXX#__*", // Row 15
		"*____________________________#XXXXXXX#__*", // Row 16
		"*____________________________###G.G###__*", // Row 17
		"*_______________________________________*", // Row 18
		"*_______________________________________*", // Row 19
		"*______________________###############__*", // Row 20
		"*__###_#H.H#_###_______#XXXXXXXXXXXXX#__*", // Row 21
		"*__#X###XXX###X#_______#XXXXXXXXXXXXX#__*", // Row 22
		"*__#XXXXXXXXXXX#_______#XXXXXXXXXXXXX#__*", // Row 23
		"*__#X###XXX###X#_______#XXXXXXXXXXXXX#__*", // Row 24
		"*__###_#H.H#_###_______#XXXXXXXXXXXXX#__*", // Row 25
		"*______________________#XXXXXXXXXXXXX#__*", // Row 26
		"*______________________######M.M######__*", // Row 27
		"*_______________________________________*", // Row 28
		"*__####P.S##____________________________*", // Row 29
		"*__#XXXXXXX#____________________________*", // Row 30
		"*__#XXXXXXX#____________________________*", // Row 31
		"*__#########____________________________*", // Row 32
		"*_______________________________________*", // Row 33
		"*______________________________#######__*", // Row 34
		"*______________________________#XXXXX#__*", // Row 35
		"*______________________________#XXXXX#__*", // Row 36
		"*______________________________##F.F##__*", // Row 37
		"*_______________________________________*", // Row 38
		"*_______________________________________*", // Row 39
		"******************#V.V#******************"  // Row 40
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
	locations.push_back(new Location("Apartment", 'A', 8, 10));
	locations.push_back(new Location("Supermarket", 'S', 20, 15));
	locations.push_back(new Location("Hospital", 'H', 12, 15));
	locations.push_back(new Location("Police Station", 'P', 7, 9));
	locations.push_back(new Location("Gas Station", 'G', 15, 8));
	locations.push_back(new Location("School", 'C', 12, 12));
	locations.push_back(new Location("Safe House", 'F', 9, 9));
	locations.push_back(new Location("Military Base", 'M', 25, 20));
	locations.push_back(new Location("Evacuation Point (Demilitarised)", 'V', 25, 20));

	populateLocationsWithZombies();
}

// Delete ALL of the dynamic locations and ground items, free up the memory
Map::~Map()
{
	for (Location* loc : locations)
	{
		delete loc;
	}
	locations.clear();

	for (Item* item : groundItems) {
		delete item;
	}
	groundItems.clear();

	for (Zombie* zombie : zombies)
	{
		delete zombie;
	}
	zombies.clear();
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
	// Impassable tiles: '*', '#', 'X', labels ('A', 'S', etc.), and obstacles ('C', 'r', '~')
	return (tile == '_' || tile == '.');
}

bool Map::isEntrance(int x, int y) const
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return false;
	return activeGrid[y][x] == '.';
}

char Map::getTileAt(int x, int y) const
{
	return activeGrid[y][x];
}

void Map::generateRandomLayout(int obstacleCount, int itemCount)
{
	// The lines needed to randomize the numbers
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution distrXPos(1, WIDTH - 1);
	std::uniform_int_distribution distrYPos(1, HEIGHT - 1);

	// The array of the obstacle types to be randomly placed and allocated
	char obstacleTypes[] = { 'C', 'r', '~' };
	int numTypes = sizeof(obstacleTypes) / sizeof(obstacleTypes[0]);

	int placed = 0;
	int attempts = 0;
	while (placed < obstacleCount && attempts < obstacleCount * 30)
	{
		int randX = distrXPos(gen);
		int randY = distrYPos(gen);

		// Check to ensure that the tile is a street tile '_'
		if (baseGrid[randY][randX] == '_')
		{
			// Next check to ensure that it is not adjacent to an entrance to the building '.'
			// Nor next to each other over distances
			// Also ensuring that no three obstacles have any chance to suround the entrance to the door
			bool nearDoorOrOtherObstacles = false;
			for (int dy = -3; dy <= 3; ++dy)
			{
				for (int dx = -3; dx <= 3; ++dx)
				{
					int checkY = randY + dy;
					int checkX = randX + dx;

					if (checkY >= 0 && checkY < HEIGHT && checkX >= 0 && checkX < WIDTH)
					{
						if (
							baseGrid[checkY][checkX] == '.' ||
							activeGrid[checkY][checkX] == 'C' ||
							activeGrid[checkY][checkX] == 'r' ||
							activeGrid[checkY][checkX] == '~'
							)
						{
							nearDoorOrOtherObstacles = true;
						}
					}
				}
			}

			// If it is safe, add the obstacle into the map
			if (!nearDoorOrOtherObstacles)
			{
				char chosenObstacle = obstacleTypes[rand() % numTypes];
				activeGrid[randY][randX] = chosenObstacle;
				placed++;
				attempts = 0;
			}
			else
			{
				attempts++;
			}
		}
		else
		{
			attempts++;
		}
	}

	int spawned = 0;
	attempts = 0;
	while (spawned < itemCount && attempts < itemCount * 30)
	{
		int randX = distrXPos(gen);
		int randY = distrYPos(gen);

		// Allowed, walkable path '_'
		if (activeGrid[randY][randX] == '_' && getGroundItemAt(randX, randY) == nullptr)
		{			
			// Next check to ensure that it is not adjacent to an entrance to the building '.'
			// Nor near any obstacles.
			// Also ensuring that no obstacles encase an item and make it in accessable
			bool nearDoorOrObstacle = false;
			for (int dy = -2; dy <= 2; ++dy)
			{
				for (int dx = -2; dx <= 2; ++dx)
				{
					int checkY = randY + dy;
					int checkX = randX + dx;

					if (checkY >= 0 && checkY < HEIGHT && checkX >= 0 && checkX < WIDTH)
					{
						if (baseGrid[checkY][checkX] == '.' || activeGrid[checkY][checkX] == 'C' || activeGrid[checkY][checkX] == 'r' || activeGrid[checkY][checkX] == '~')
						{
							nearDoorOrObstacle = true;
						}
					}
				}
			}

			// If it is safe, add the item into the map
			if (!nearDoorOrObstacle)
			{
				int type = rand() % 4;
				Item* newItem = nullptr;

				if (type == 0) newItem = new Food();
				else if (type == 1) newItem = new Water();
				else if (type == 2) newItem = new Medicine();
				else if (type == 3) newItem = new Ammunition();

				newItem->setPosition(randX, randY);
				addGroundItem(newItem);
				spawned++;
				attempts = 0;
			}
			else
			{
				attempts++;
			}
		}
		else
		{
			attempts++;
		}
	}
}

void Map::randomiseLocationLayouts(float furnitureDensity, float itemDensity)
{
	for (Location* location : locations)
	{
		float locationFurnitures = furnitureDensity;
		float locationItems = itemDensity;

		if (location->getSymbol() == 'V')
		{
			locationFurnitures *= 2.0;
			locationItems *= 0.25;
		}

		int area = location->getInteriorFloorArea();
		location->generateRandomLayout(static_cast<int>(area * locationFurnitures), static_cast<int>(area * locationItems));
	}
}

void Map::populateLocationsWithZombies(float zombieDensity)
{
	for (Location* location : locations)
	{
		char sym = location->getSymbol();
		
		// Apartment and Safe House should not have any zombies
		if (sym == 'A' || sym == 'F') {
			continue;
		} 

		float density = zombieDensity;

		if (sym == 'V') {
			density = zombieDensity * 3.0f; // Evacuation point is heavily infested
		}

		int zombieCount = static_cast<int>(location->getInteriorFloorArea() * density);
		if (zombieCount > 0)
		{
			location->spawnRandomZombies(zombieCount);
		}
	}
}

void Map::spawnRandomZombies(int zombieCount)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrX(0, WIDTH - 1), distrY(0, HEIGHT - 1);

	int spawned = 0;
	int attempts = 0;
	while (spawned < zombieCount && attempts < zombieCount * 30)
	{
		int randomX = distrX(gen);
		int randomY = distrY(gen);

		if (isWalkable(randomX, randomY) && getZombieAt(randomX, randomY) == nullptr)
		{
			zombies.push_back(new Zombie("Zombie", "A shambling infected corpse.", randomX, randomY, 'Z', 40, 40, 5));
			spawned++;
			attempts = 0;
		}
		else
		{
			attempts++;
		}
	}
}

void Map::randomizeAllLocationLayouts(int furnitureCount, int itemCount)
{
	for (Location* loc : locations) {
		loc->generateRandomLayout(furnitureCount, itemCount);
	}
}

void Map::updateZombies(int playerX, int playerY)
{
	for (Zombie* zombie : zombies)
	{
		if (zombie->getIsAlive())
		{
			zombie->moveRandomly(0, 0, WIDTH - 1, HEIGHT - 1, [this, playerX, playerY](int x, int y)
                {
                    return isWalkable(x, y) && getZombieAt(x, y) == nullptr && !(x == playerX && y == playerY);
                }
            );
		}
	}
}

void Map::removeZombie(Zombie * target)
{
	zombies.erase(std::remove(zombies.begin(), zombies.end(), target), zombies.end());
	delete target;
}

void Map::displayMap(int playerX, int playerY, int viewWidth, int viewHeight, Player& player) const
{
	// Calculate raw top-left offset
	int rawCamX = playerX - (viewWidth / 2);
	int rawCamY = playerY - (viewHeight / 2);

	// Clamp camera within map bounds
	int camX = std::clamp(rawCamX, 0, WIDTH - viewWidth);
	int camY = std::clamp(rawCamY, 0, HEIGHT - viewHeight);

	std::cout << "========================================" << std::endl;
	for (int r = camY; r < camY + viewHeight; ++r)
	{
		for (int c = camX; c < camX + viewWidth; ++c)
		{

			Item* grounditem = getGroundItemAt(c, r);
			Zombie* zombie = getZombieAt(c, r);

			if (r == playerY && c == playerX) { // To render the Player
				std::cout << player.getColouredSymbol() << " "; // Player character
			}
			else if (zombie != nullptr) {
				std::cout << zombie->getColouredSymbol() << " "; // Render the Zombie
			}
			else if (grounditem != nullptr) {
				std::cout << grounditem->getColouredSymbol() << " "; // Item to render
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

void Map::addGroundItem(Item* item)
{
	if (item == nullptr) return;
	item->setInInventory(false);

	// Prevent overlapping: if target space already has an item, drop in adjacent walkable spot
	if (getGroundItemAt(item->getX(), item->getY()) != nullptr)
	{
		int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };
		int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };

		for (int i = 0; i < 8; ++i)
		{
			int newX = item->getX() + dx[i];
			int newY = item->getY() + dy[i];

			if (isWalkable(newX, newY) && getGroundItemAt(newX, newY) == nullptr)
			{
				item->setPosition(newX, newY);
				break;
			}
		}
	}

	groundItems.push_back(item);
}

Item* Map::pickupItemAt(int playerX, int playerY)
{
	for (auto it = groundItems.begin(); it != groundItems.end(); ++it)
	{
		if ((*it)->getX() == playerX && (*it)->getY() == playerY) {
			Item* picked = *it;
			groundItems.erase(it); // Remove from map list so it no longer renders
			picked->setInInventory(true);
			return picked;
		}
	}
	return nullptr;
}

Item* Map::getGroundItemAt(int x, int y) const
{
	for (Item* item : groundItems)
	{
		if (item->getX() == x && item->getY() == y) {
			return item;
		}
	}
	return nullptr;
}

Location* Map::getLocationByName(std::string name) 
{
	for (Location* location : locations)
	{
		if (location->getName() == name)
		{
			return location;
		}
	}
	return nullptr;
}

Zombie* Map::getZombieAt(int x, int y) const
{
	for (Zombie* zombie : zombies)
	{
		if (zombie->getIsAlive() && zombie->getX() == x && zombie->getY() == y)
		{
			return zombie;
		}
	}
	return nullptr;
}
