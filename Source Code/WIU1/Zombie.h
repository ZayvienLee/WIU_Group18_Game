#pragma once
#include "Entity.h"
#include <string>

class Map;
class Location;

class Zombie : public Entity
{
public:
	Zombie(std::string n, std::string desc, int x, int y, char sym, int h, int maxH, int atk, bool alive = true);
	~Zombie();

	/* Overidden from Entity class */
	void update() override;

	/* Zombies move randomly based on the action taken and if there are any obstacles in the way*/
	void moveRandomly(int minX, int minY, int maxX, int maxY, Map* map = nullptr, Location* loc = nullptr);
};