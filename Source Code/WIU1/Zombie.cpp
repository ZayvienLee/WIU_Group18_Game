#include <string>
#include <random>
#include "Zombie.h"
#include "GameObject.h"
#include "Location.h"
#include "Map.h"

Zombie::Zombie(std::string n, std::string desc, int x, int y, char sym, int h, int maxH, int atk, bool alive)
{
	// GameObject variables
	name = n;
	description = desc;
	symbol = sym;

	// Set up the coordinates
	positionX = x;
	positionY = y;

	// Entity variables
	health = h;
	maxHealth = maxH;
	attackPower = atk;
	isAlive = alive; // Entity is alive by default. Always

	colourCode = Colour::BOLD_RED;
}

Zombie::~Zombie()
{

}

void Zombie::update()
{
	// Movement is driven externally
}

void Zombie::moveRandomly(int minX, int minY, int maxX, int maxY, Map* map, Location* loc)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dirDist(0, 4); // Based on the number, the zombie will stay or change position

	// Randomize the zombie's position
	int dir = dirDist(gen);
	int newX = positionX, newY = positionY;

	if (dir == 1) newY--;
	else if (dir == 2) newY++;
	else if (dir == 3) newX--;
	else if (dir == 4) newX++;

	// To check the bounds first
	if (newX < minX || newX > maxX || newY < minY || newY > maxY)
	{
		return; // Out of bounds, stop early and don't move
	}

	bool isWalkable = false;

	if (loc != nullptr)
	{
		isWalkable = loc->isIndoorWalkable(newX, newY) && loc->getZombieAt(newX, newY) == nullptr && loc->getNPCat(newX, newY) == nullptr;
	}
	else if (map != nullptr)
	{
		isWalkable = map->isWalkable(newX, newY) && map->getZombieAt(newX, newY) == nullptr;
	}

	if (isWalkable) // Move if there are no obstacles
	{
		positionX = newX;
		positionY = newY;
	}
}