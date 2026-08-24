#include "Zombie.h"
#include <string>
#include <random>
#include <functional>

Zombie::Zombie(std::string n, std::string desc, int x, int y, char sym, int h, int maxH, int atk, bool alive)
{
	// GameObject variables
	name = n;
	description = desc;
	symbol = sym;

	// Entity variables
	health = h;
	maxHealth = maxH;
	attackPower = atk;
	isAlive = alive; // Entity is alive by default. Always

	// Set up the coordinates
	ZombOutdoorX = 1;
	ZombOutdoorY = 1;
	ZombIndoorX = 0;
	ZombIndoorY = 0;
}

void Zombie::update()
{
	// Movement is driven externally
}

void Zombie::moveRandomly(int minX, int minY, int maxX, int maxY, std::function<bool(int, int)> isWalkable)
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

	if (newX >= minX && newX <= maxX && newY >= minY && newY <= maxY && isWalkable(newX, newY))
	{
		positionX = newX;
		positionY = newY;
	}
}

std::string Zombie::getZName() const
{
	return name;
}

int Zombie::getZOutdoorX() const
{
	return ZombOutdoorX;
}

int Zombie::getZOutdoorY() const
{
	return ZombOutdoorY;
}

void Zombie::setZOutdoorPosition(int x, int y)
{
	ZombOutdoorX = x;
	ZombOutdoorY = y;
}

int Zombie::getZIndoorX() const
{
	return ZombIndoorX;
}

int Zombie::getZIndoorY() const
{
	return ZombIndoorY;
}

void Zombie::setZIndoorPosition(int x, int y)
{
	ZombIndoorX = x;
	ZombIndoorY = y;
}
