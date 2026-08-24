#pragma once
#include "Entity.h"
#include <string>
#include <functional>

class Zombie : public Entity
{
private:
	int ZombOutdoorX, ZombOutdoorY;
	int ZombIndoorX, ZombIndoorY;
public:
	Zombie(std::string n, std::string desc, int x, int y, char sym, int h, int maxH, int atk, bool alive = true);

	/* Overidden from Entity class */
	void update() override;

	/* std::function is used to check before walking to avoid using map or location; could cause a circluar include */
	void moveRandomly(int minX, int minY, int maxX, int maxY, std::function<bool(int, int)> isWalkable);

	/* Variable Accessors */
	std::string getZName() const;

	/* Outdoor Position Accessors */
	int getZOutdoorX() const;
	int getZOutdoorY() const;
	void setZOutdoorPosition(int x, int y);

	/* Indoor Position Accessors */
	int getZIndoorX() const;
	int getZIndoorY() const;
	void setZIndoorPosition(int x, int y);
};