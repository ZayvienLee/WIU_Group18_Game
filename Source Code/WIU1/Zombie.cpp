#include "Zombie.h"

Zombie::Zombie(std::string n, int h, int maxH)
{
	// GameObject variables
	name = n;
	description = "Description";
	symbol = 'Z';

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
