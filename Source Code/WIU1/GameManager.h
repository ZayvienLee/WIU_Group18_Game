#pragma once
#include "Map.h"
#include "Player.h"
#include "Location.h"

class GameManager
{
private:
	Map outdoorMap;
	Location* currentBuilding; // Pointer to the building's interior if indoors
	Player* player;

	bool isInBuilding;

	// Save the outdoor coordinates when stepping inside
	int savedOutdoorX;
	int savedOutdoorY;

public:
	GameManager();
	~GameManager();
	void handlePlayerInput(char moveCommand); // Route movement depends on the player location
	void enterBuilding(Location* Building);
	void exitBuilding();

};