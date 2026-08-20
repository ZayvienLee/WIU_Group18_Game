#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "Location.h"
#include <iostream>
#include <cctype>
#include "Item.h"

// To add later on with the map and location, etc. To fix the warning and errors and add the 
// necessary logic for each of them.

GameManager::GameManager()
{
    player = new Player("Name", "The Player", 'P', 100, 100, 100, 100, 10, true, 20);
	isInBuilding = false;
	currentBuilding = nullptr;
	savedOutdoorX = 0;
	savedOutdoorY = 0;
}

GameManager::~GameManager()
{
    delete player;
}

void GameManager::handlePlayerInput(char moveCommand)
{
	// Convert to uppercase
	moveCommand = toupper(moveCommand);

	if (isInBuilding)
	{
		// Indoor Movement Logic

        int nextX = player->getIndoorX();
        int nextY = player->getIndoorY();

        if (moveCommand == 'W') nextY--; // Up
        else if (moveCommand == 'S') nextY++; // Down
        else if (moveCommand == 'A') nextX--; // Left
        else if (moveCommand == 'D') nextX++; // Right

        // Check building interior collision
        if (currentBuilding->isIndoorWalkable(nextX, nextY))
        {
            player->setIndoorPosition(nextX, nextY);

            // Check if player stepped on the interior Exit Door ('E')
            if (currentBuilding->getTileAt(nextX, nextY) == 'E')
            {
                std::cout << "[INFO] Exiting building..." << std::endl;
                exitBuilding();
            }
        }
        else
        {
            std::cout << "[COLLISION] You bumped into an interior wall/furniture!" << std::endl;
        }
	}
    else
    {
        // Outdoor Movement Logic

        int nextX = player->getOutdoorX();
        int nextY = player->getOutdoorY();

        if (moveCommand == 'W') nextY--; // Up
        else if (moveCommand == 'S') nextY++; // Down
        else if (moveCommand == 'A') nextX--; // Left
        else if (moveCommand == 'D') nextX++; // Right

        // Check outdoor collision
        if (outdoorMap.isWalkable(nextX, nextY)) {
            player->setOutdoorPosition(nextX, nextY);
        }
        else {
            std::cout << "[COLLISION] Cannot move there!" << std::endl;
        }

        // Action: Press 'E' to enter building if standing on entrance tile '.'
        if (moveCommand == 'E' && outdoorMap.isEntrance(player->getOutdoorX(), player->getOutdoorY())) {
            // Identify building based on coordinates or adjacent label
            Location* targetBuilding = outdoorMap.getBuildingAt(player->getOutdoorX(), player->getOutdoorY());
            if (targetBuilding != nullptr) {
                enterBuilding(targetBuilding);
            }
        }
    }
}

// Transition into a building
void GameManager::enterBuilding(Location* building) {
    isInBuilding = true;
    currentBuilding = building;

    // Save outdoor position so player can return to the exact same tile when leaving
    savedOutdoorX = player->getOutdoorX();
    savedOutdoorY = player->getOutdoorY();

    // Set indoor starting spawn (e.g., bottom center of the building interior array)
    player->setIndoorPosition(building->getSpawnX(), building->getSpawnY());

    std::cout << "[ENTERED] Welcome to " << building->getName() << std::endl;
}

// Transition out of a building
void GameManager::exitBuilding() {
    isInBuilding = false;
    currentBuilding = nullptr;

    // Restore outdoor position
    player->setOutdoorPosition(savedOutdoorX, savedOutdoorY);
}

void GameManager::handleItemPickup(Player& player, Map& currentMap)
{
    int pX = player.getOutdoorX();
    int pY = player.getOutdoorY();

    Item* groundItem = currentMap.pickupItemAt(pX, pY);
    if (groundItem != nullptr) {
        // Sync item position to player coordinates
        groundItem->syncWithPlayer(pX, pY);

        if (player.addItem(groundItem)) {
            std::cout << "[PICKUP] Added " << groundItem->getName() << " to inventory!" << std::endl;
        }
        else {
            // Inventory full: place back on the ground
            currentMap.addGroundItem(groundItem);
            std::cout << "[FULL] Inventory full! Could not pick up item." << std::endl;
        }
    }
}

void GameManager::handleItemDrop(Player& player, Map& currentMap, int slotNumber)
{
    Item* droppedItem = player.getItemByNumber(slotNumber);

    if (droppedItem != nullptr) {
        // 1. Remove from inventory array slot
        player.removeItemSlot(slotNumber);

        // 2. Set item position to player's current location
        droppedItem->setPosition(player.getOutdoorX(), player.getOutdoorY());

        // 3. Add to map ground list (now visible on rendering)
        currentMap.addGroundItem(droppedItem);

        std::cout << "[DROPPED] " << droppedItem->getName() << " placed on ground." << std::endl;
    }
}

void GameManager::rewardPlayerFromNPC(Player& player, Map& currentMap, Item* questReward) {
    std::cout << "[NPC] 'Here, take this " << questReward->getName() << " for your help.'" << std::endl;

    // Item starts directly in inventory, matching player position
    questReward->syncWithPlayer(player.getOutdoorX(), player.getOutdoorY());
    questReward->setInInventory(true);

    if (!player.addItem(questReward)) {
        // Fallback: If inventory is full when NPC gives reward, drop it at player's feet
        std::cout << "[NPC] 'Your bags are full. I'll leave it right here on the ground.'" << std::endl;
        questReward->setPosition(player.getOutdoorX(), player.getOutdoorY());
        currentMap.addGroundItem(questReward);
    }
}