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
	int savedOutdoorX; // Save the outdoor coordinates of X when stepping inside
	int savedOutdoorY; // Save the outdoor coordinates of Y when stepping inside
	
	StoryManager storyManager;

public:
	GameManager();
	~GameManager();

	void handlePlayerInput(char moveCommand); // Route movement depends on the player location
	void checkGroundItemInspection(); // needed to check if the item is on the same space as the player after moving

	void enterBuilding(Location* Building);
	void exitBuilding();

	void checkZombieAttacks();
	void updateZombiePositions();

	void interactWithNPC();

	/* If the player does not find or use the supplies, penalise the player */
	void applySurvivalPenalties();

	/* To handle Item management */
	void handleItemPickup();
	void handleItemDrop(int slotNumber);
	void rewardPlayerFromNPC(Player& playerRef, Map& mapRef, Item* questReward) const;
	void handlePlayerAttack(char choice);

	// Renders either the camera viewport or building interior
	void render(int viewWidth = 15, int viewHeight = 9) const;

	/* Variable Acessors */
	bool getLocationStatus() const;
	Player* getPlayer();
	StoryManager& getStoryManager();
	Map& getMap();
};