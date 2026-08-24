#pragma once
#include "Entity.h"
#include <string>
#include <functional>

class Zombie : public Entity
{
public:
	Zombie(std::string n, std::string desc, int x, int y, char sym, int h, int maxH, int atk, bool alive = true);

	/* Overidden from Entity class */
	void update() override;

	/* std::function is used to check before walking to avoid using map or location; could cause a circluar include */
	void moveRandomly(int minX, int minY, int maxX, int maxY, std::function<bool(int, int)> isWalkable);
};