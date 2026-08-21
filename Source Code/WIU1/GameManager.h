#pragma once
#include "Map.h"
#include "Player.h"
#include "Location.h"
#include "Item.h"
#include "StoryManager.h"

class Player; // Forward declaration to avoid circular include

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
	
	StoryManager storyManager;

public:
	GameManager();
	~GameManager();
	void handlePlayerInput(char moveCommand); // Route movement depends on the player location
	void enterBuilding(Location* Building);
	void exitBuilding();

	/* To handle Item management */
	void handleItemPickup(Player& player, Map& currentMap) const;
	void handleItemDrop(Player& player, Map& currentMap, int slotNumber) const;
	void rewardPlayerFromNPC(Player& player, Map& currentMap, Item* questReward) const;

	// Renders either the camera viewport or building interior
	void render(int viewWidth = 15, int viewHeight = 9) const;

	StoryManager& getStoryManager();
};