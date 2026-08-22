#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "Location.h"
#include <iostream>
#include <cctype>
#include "Item.h"
#include "StoryManager.h"

// To add later on with the map and location, etc. To fix the warning and errors and add the 
// necessary logic for each of them.

GameManager::GameManager()
{
    player = new Player("Name", "The Player", 'P', 100, 100, 100, 100, 10, true, 20);
	isInBuilding = false;
	currentBuilding = nullptr;
	savedOutdoorX = 0;
	savedOutdoorY = 0;

    Location* supermarket = outdoorMap.getLocationByName("Supermarket");
    Location* policeStation = outdoorMap.getLocationByName("Police Station");
    Location* hospital = outdoorMap.getLocationByName("Hospital");

    if (supermarket != nullptr) {
        supermarket->addNPC(&storyManager.getZombieNPC());
    }
    if (policeStation != nullptr) {
        policeStation->addNPC(&storyManager.getmissingpersonNPC());
    }
    if (hospital != nullptr) {
        hospital->addNPC(&storyManager.getpharmacyNPC());
    }
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

void GameManager::checkGroundItemInspection()
{
    int pX = isInBuilding ? player->getIndoorX() : player->getOutdoorX();
    int pY = isInBuilding ? player->getIndoorY() : player->getOutdoorY();
    
    Item* groundItem = outdoorMap.getGroundItemAt(pX, pY);
    if (groundItem != nullptr)
    {
        std::cout << "\n[GROUND ITEM DETECTED]" << std::endl
            << "  Name: " << groundItem->getName() << std::endl
            << "  Qty: " << groundItem->getQuantity() << " | Weight: " << groundItem->getWeight() << " g" << std::endl
            << "  Info: " << groundItem->getDescription() << std::endl
            << "  -> Press [E] to pick up this item." << std::endl;
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

    std::cout << "[ENTERED] Welcome inside the " << building->getName() << std::endl;
}

// Transition out of a building
void GameManager::exitBuilding() {
    isInBuilding = false;
    currentBuilding = nullptr;

    // Restore outdoor position
    player->setOutdoorPosition(savedOutdoorX, savedOutdoorY);
}

void GameManager::handleItemPickup()
{
    int pX = isInBuilding ? player->getIndoorX() : player->getOutdoorX();
    int pY = isInBuilding ? player->getIndoorY() : player->getOutdoorY();

    Item* groundItem = isInBuilding ? currentBuilding->pickupItemAt(pX, pY) : outdoorMap.pickupItemAt(pX, pY);
    if (groundItem == nullptr)
    {
        std::cout << "[PICKUP] No item to pick up here!" << std::endl;
        return;
    }
    else if (player->addItem(groundItem))
    {
        std::cout << "[PICKUP] Added " << groundItem->getName() << " to inventory!" << std::endl;
    }
    else
    {
        // Inventory is full: place item back onto ground
        isInBuilding ? currentBuilding->addFloorItem(groundItem) : outdoorMap.addGroundItem(groundItem);
        std::cout << "[FULL] Inventory full! Could not pick up item." << std::endl;
    }
}

void GameManager::handleItemDrop(int slotNumber)
{
    Item* droppedItem = player->getItemByNumber(slotNumber);

    int xPosLoc = isInBuilding ? player->getIndoorX() : player->getOutdoorX();
    int yPosLoc = isInBuilding ? player->getIndoorY() : player->getOutdoorY();

    if (droppedItem != nullptr)
    {
        player->removeItem(droppedItem, slotNumber); // Remove from inventory array slot
        droppedItem->setPosition(xPosLoc, yPosLoc); // Set item position to player's current location

        // Add to map ground list (now visible on rendering)
        // Also to handle the non-overlapping placement
        isInBuilding ? currentBuilding->addFloorItem(droppedItem) : outdoorMap.addGroundItem(droppedItem);

        std::cout << "[DROPPED] " << droppedItem->getName() << " placed on ground." << std::endl;
    }
    else
    {
        std::cout << "[INVALID] The target slot does not have any item." << std::endl;
    }
}

void GameManager::rewardPlayerFromNPC(Player& playerRef, Map& mapRef, Item* questReward) const
{
    std::cout << "[NPC] 'Here, take this " << questReward->getName() << " for your help.'" << std::endl;

    int xPosLoc = isInBuilding ? playerRef.getIndoorX() : playerRef.getOutdoorX();
    int yPosLoc = isInBuilding ? playerRef.getIndoorY() : playerRef.getOutdoorY();

    // Item starts directly in inventory, matching player position based on the area the player is at
    questReward->syncWithPlayer(xPosLoc, yPosLoc);
    questReward->setInInventory(true);

    if (!playerRef.addItem(questReward)) {
        // Fallback: If inventory is full when NPC gives reward, drop it at player's feet
        std::cout << "[NPC] 'Your bags are full. I'll leave it right here on the ground.'" << std::endl;
        questReward->setPosition(xPosLoc, yPosLoc);
        mapRef.addGroundItem(questReward);
    }
}

void GameManager::render(int viewWidth, int viewHeight) const
{
    if (isInBuilding && currentBuilding != nullptr)
    {
        // Renders 10x10 interior grid centered on player indoor coordinates
        currentBuilding->displayInterior(player->getIndoorX(), player->getIndoorY());
    }
    else
    {
        // Renders outdoor map viewport centered on player outdoor coordinates
        outdoorMap.displayMap(player->getOutdoorX(), player->getOutdoorY(), viewWidth, viewHeight, *player);
    }
}

bool GameManager::getLocationStatus() const
{
    return isInBuilding;
}

Player* GameManager::getPlayer()
{
    return player;
}

StoryManager& GameManager::getStoryManager()
{
    return storyManager;
}

Map& GameManager::getMap()
{
    return outdoorMap;
}
