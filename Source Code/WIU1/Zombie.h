#pragma once
#include "Entity.h"
#include <string>

class Zombie : public Entity
{
private:
	int ZombOutdoorX, ZombOutdoorY;
	int ZombIndoorX, ZombIndoorY;
public:
	Zombie(std::string n, std::string desc, char sym, int h, int maxH, int atk, bool alive);

	/* Overidden from Entity class */
	void update() override;

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