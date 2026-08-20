#include "Zombie.h"

Zombie::Zombie(std::string n, std::string desc, char sym, int h, int maxH, int atk, bool alive)
{
	// GameObject variables
	name = n;
	description = desc;
	symbol = sym;

	// Entity variables
	health = h;
	maxHealth = maxH;
	isAlive = true; // Entity is alive by default. Always

	// Set up the coordinates
	ZombOutdoorX = 1;
	ZombOutdoorY = 1;
	ZombIndoorX = 0;
	ZombIndoorY = 0;
}

void Zombie::update()
{
	
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
