#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "Location.h"
#include <iostream>
#include <cctype>
#include "Item.h"
#include "StoryManager.h"
#include "Weapon.h"
#include "Zombie.h"
#include "NPC.h"
#include "Quest.h"
#include "KeyCard.h"

// To add later on with the map and location, etc. To fix the warning and errors and add the 
// necessary logic for each of them.

GameManager::GameManager()
{
    player = new Player("Name", "The Player", 'P', 100, 100, 100, 100, 10, true, 20);
	isInBuilding = false;
	currentBuilding = nullptr;
	savedOutdoorX = 20;
	savedOutdoorY = 4;

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

    /* The player gets the necessary placements in the game accordingly. */
    Location* apartment = outdoorMap.getLocationByName("Apartment");
    if (apartment != nullptr)
    {
        isInBuilding = true;
        currentBuilding = apartment;
        player->setIndoorPosition(apartment->getSpawnX(), apartment->getSpawnY());

        player->equipWeapon(new Weapon("Knife", "A rusty kitchen knife. Reliable up close.", 'k', 15, 1, 200));
    }

    hasWon = false;
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
        if (currentBuilding->isIndoorWalkable(nextX, nextY) && currentBuilding->getZombieAt(nextX, nextY) == nullptr)
        {
            player->setIndoorPosition(nextX, nextY);

            // Check if player stepped on the interior Exit Door ('E')
            if (currentBuilding->getTileAt(nextX, nextY) == 'E')
            {
                std::cout << "[INFO] Exiting building..." << std::endl;
                exitBuilding();
            }
        }
        else if (currentBuilding->getZombieAt(nextX, nextY) != nullptr)
        {
            std::cout << "[BLOCKED] A zombie is in your way! Press [F] to attack it." << std::endl;
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
        if (outdoorMap.isWalkable(nextX, nextY) && outdoorMap.getZombieAt(nextX, nextY) == nullptr) {
            player->setOutdoorPosition(nextX, nextY);
            
            // Decrease hunger and thirst accordingly
            player->setHunger(player->getHunger() - 1);
            player->setThirst(player->getThirst() - 1);
            applySurvivalPenalties();
        }
        else if (outdoorMap.getZombieAt(nextX, nextY) != nullptr)
        {
            std::cout << "[BLOCKED] A zombie is in your way! Press [F] to attack it." << std::endl;
        }
        else
        {
            std::cout << "[COLLISION] Cannot move there!" << std::endl;
        }

        // Action: Press 'E' to enter building if standing on entrance tile '.'
        if (moveCommand == 'E' && outdoorMap.isEntrance(player->getOutdoorX(), player->getOutdoorY())) {
            // Identify building based on coordinates or adjacent label
            Location* targetBuilding = outdoorMap.getBuildingAt(player->getOutdoorX(), player->getOutdoorY());
            if (targetBuilding != nullptr) {
                if (targetBuilding->getName() == "Safe House" && player->findItemByName("Key Card") == nullptr)
                {
                    std::cout << "[LOCKED] This door needs a keycard. Complete all quests to obtain one." << std::endl;
                }
                else if (targetBuilding->getName() == "Evacuation Point")
                {
                    if (checkEvacuationScreening())
                    {
                        hasWon = true;
                    }
                }
                else
                {
                    enterBuilding(targetBuilding);
                }
            }
        }
    }

    updateZombiePositions();

    checkZombieAttacks();       // zombies now next to you get a hit in
    applySurvivalPenalties();   // starving/dehydrated damage, if applicable
}

void GameManager::checkGroundItemInspection()
{
    int pX = isInBuilding ? player->getIndoorX() : player->getOutdoorX();
    int pY = isInBuilding ? player->getIndoorY() : player->getOutdoorY();
    
    Item* groundItem = isInBuilding ? currentBuilding->getFloorItemAt(pX, pY) : outdoorMap.getGroundItemAt(pX, pY);
    if (groundItem != nullptr)
    {
        std::cout << std::endl << "[ITEM DETECTED]" << std::endl
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

void GameManager::checkZombieAttacks()
{
    int pX = isInBuilding ? player->getIndoorX() : player->getOutdoorX();
    int pY = isInBuilding ? player->getIndoorY() : player->getOutdoorY();

    // 4-directional adjacency — any zombie standing next to you gets a free hit each turn.
    // Being surrounded by more than one is deliberately worse: each adjacent zombie hits.
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    for (int i = 0; i < 4; ++i)
    {
        int checkX = pX + dx[i];
        int checkY = pY + dy[i];

        Zombie* zombie = isInBuilding ? currentBuilding->getZombieAt(checkX, checkY) : outdoorMap.getZombieAt(checkX, checkY);

        if (zombie != nullptr)
        {
            player->takeDamage(zombie->getAttackPower());
            std::cout << "[ZOMBIE] " << zombie->getName() << " claws at you!" << std::endl;
        }
    }
}

void GameManager::updateZombiePositions()
{
    // Check if the player is in building or not
    if (isInBuilding) {
        if (currentBuilding != nullptr) {
            currentBuilding->updateZombies(player->getIndoorX(), player->getIndoorY());
        }
    }
    else {
        outdoorMap.updateZombies(player->getOutdoorX(), player->getOutdoorY());
    }
}

void GameManager::applySurvivalPenalties()
{
    if (player->getHunger() <= 10 || player->getThirst() <= 10) {
        player->takeDamage(2);
    }
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

void GameManager::handlePlayerAttack(char choice)
{
    Weapon* weapon = player->getWeapon();
    if (weapon == nullptr) {
        std::cout << "[ATTACK] No weapon was equipped! Press [U] to equip a weapon." << std::endl;
        return;
    }

    // Based on choice, set direction accordingly
    int dx = 0, dy = 0;
    if (choice == 'W') dy = -1;
    else if (choice == 'S') dy = 1;
    else if (choice == 'A') dx = -1;
    else if (choice == 'D') dx = 1;
    else return;

    bool isRanged = weapon->getAtkRange() > 1;
    if (isRanged && player->getAmmoCount() <= 0) {
        std::cout << "[ATTACK] Out of ammo!" << std::endl;
        return;
    }

    // The initial position of the player,
    // which will check if the weapon's range is close to a zombie.
    int positionX = isInBuilding ? player->getIndoorX() : player->getOutdoorX();
    int positionY = isInBuilding ? player->getIndoorY() : player->getOutdoorY();

    // Based on the range, the steps will increment
    for (int step = 1; step <= weapon->getAtkRange(); ++step)
    {
        int currentX = positionX + (dx * step);
        int currentY = positionY + (dy * step);

        // Search the adjacent tiles to check if a zombie is nearby
        Zombie* target = isInBuilding ? currentBuilding->getZombieAt(currentX, currentY) : outdoorMap.getZombieAt(currentX, currentY);

        if (target != nullptr)
        {
            target->takeDamage(weapon->getDamage());
            if (isRanged) player->setAmmoCount(player->getAmmoCount() - 1);

            if (!target->getIsAlive())
            {
                std::cout << "[KILL] " << target->getName() << " destroyed!" << std::endl;
                isInBuilding ? currentBuilding->removeZombie(target) : outdoorMap.removeZombie(target);
            }
            else
            {
                std::cout << "[ATTACK] " << target->getName() << " is attacked!" << std::endl;
                std::cout << "Damage: " << weapon->getDamage() << ", " << target->getName() << " Health: " << target->getHealth() << std::endl;
            }

            checkZombieAttacks();   // zombies now next to you get a hit on the player

            return;
        }
        if (!isRanged) break; // melee only checks the one adjacent tile
    }
    std::cout << "[ATTACK] No target in range." << std::endl;

    updateZombiePositions();
}

void GameManager::render(int viewWidth, int viewHeight) const
{
    if (isInBuilding && currentBuilding != nullptr)
    {
        // Renders 10x10 interior grid centered on player indoor coordinates
        currentBuilding->displayInterior(player->getIndoorX(), player->getIndoorY(), *player);
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

bool GameManager::checkNPCInteraction()
{
    
}

void GameManager::talkToNPC(NPC* npc)
{
    /* This is to check if all of the quests are completed */
    if (storyManager.allQuestsCompleted() && player->findItemByName("Key Card") == nullptr)
    {
        KeyCard* keycard = new KeyCard();
        
        if (player->addItem(keycard))
        {
            std::cout << std::endl << "[RADIO] All primary objectives complete. A keycard to the Safe House has been left for you." << std::endl;
        }
        else
        {
            int xPos = isInBuilding ? player->getIndoorX() : player->getOutdoorX();
            int yPos = isInBuilding ? player->getIndoorY() : player->getOutdoorY();

            keycard->setPosition(xPos, yPos);

            isInBuilding ? currentBuilding->addFloorItem(keycard) : outdoorMap.addGroundItem(keycard);
            std::cout << std::endl << "[RADIO] All objectives complete! A keycard was dropped at your feet, as your bags are full." << std::endl;
        }
    }
}

bool GameManager::checkEvacuationScreening()
{
    if (!storyManager.allQuestsCompleted())
    {
        std::cout << "[SCREENING] Guard: \"We can't let you through yet — finish what you started in the city first.\"" << std::endl;
        return false;
    }

    if (player->findItemByName("Key Card") == nullptr)
    {
        std::cout << "[SCREENING] Guard: \"Where's your clearance? Report to the Safe House first.\"" << std::endl;
        return false;
    }

    std::cout << std::endl << "[SCREENING] Guard: \"Papers check out. Welcome to Haven-7, survivor.\"" << std::endl;
    return true;
}

bool GameManager::getHasWon() const
{
    return hasWon;
}

void GameManager::interactWithNPC()
{
    if (!isInBuilding || currentBuilding == nullptr)
    {
        return;
    }

    int playerX = player->getIndoorX();
    int playerY = player->getIndoorY();

    NPC* npc = currentBuilding->getNPCat(playerX + 1, playerY);

    if (npc == nullptr)
    {
        npc = currentBuilding->getNPCat(playerX - 1, playerY);
    }

    if (npc == nullptr)
    {
        npc = currentBuilding->getNPCat(playerX, playerY + 1);
    }

    if (npc == nullptr)
    {
        npc = currentBuilding->getNPCat(playerX, playerY - 1);
    }

    if (npc != nullptr)
    {
        npc->talk();
    }
}
