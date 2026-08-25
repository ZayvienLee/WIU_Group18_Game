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
#include "Temozolomide.h"

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
    Location* safehouse = outdoorMap.getLocationByName("Safe House");

    if (supermarket != nullptr) {
        supermarket->addNPC(&storyManager.getZombieNPC());
        Temozolomide* temozolomide = new Temozolomide();
        temozolomide->setPosition(5, 5);

        supermarket->addFloorItem(temozolomide);
    }
    if (policeStation != nullptr) {
        policeStation->addNPC(&storyManager.getmissingpersonNPC());
    }
    if (hospital != nullptr) {
        hospital->addNPC(&storyManager.getpharmacyNPC());
    }

    if (safehouse != nullptr) {
        safehouse->addNPC(&storyManager.getTimothyNPC());
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
                enterBuilding(targetBuilding);
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

        if (groundItem->getName() == "Temozolomide" && storyManager.getfindPharmacyQuest().isAccepted())
        {
            storyManager.findTemozolomide();

            std::cout << "You found the Temozolomide!" << std::endl;
            std::cout << "Return to Dr. Chen" << std::endl;
        }
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
                storyManager.addZombieKill();
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

bool GameManager::hasTemozolomide()
{
    for (int i = 0; i < player->getItemCount(); i++)
    {
        Item* item = player->getItemByNumber(i);

        if (item != nullptr && item->getName() == "Temozolomide")
        {
            return true;
        }
    }
    return false;

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

    if (npc == &storyManager.getTimothyNPC())
    {
        if (storyManager.getfindMissingPersonQuest().isAccepted())
        {
            storyManager.findTimothy();

            std::cout << "Timothy: Thank you for finding me!" << std::endl;
            std::cout << "Return to Hank" << std::endl;
        }
        else
        {
            std::cout << "Timothy: I don't know you" << std::endl;
        }

        return;
    }

    if (npc == &storyManager.getmissingpersonNPC())
    {
        Quest& quest = storyManager.getfindMissingPersonQuest();
        
        if (!quest.isAccepted())
        {
            npc->talk();
        }
        else if (storyManager.isTimothyFound())
        {
            quest.completeQuest();

            std::cout << "Hank: You found Timothy!" << std::endl;
            std::cout << "Quest Completed!" << std::endl;
        }
        else
        {
            std::cout << "Hank: Please find Timothy first." << std::endl;
        }

        return;
    }

    if (npc == &storyManager.getZombieNPC())
    {
        Quest& quest = storyManager.getkillZombieQuest();

        if (!quest.isAccepted())
        {
            npc->talk();
        }
        else if (storyManager.getZombiesKilled() >= 3)
        {
            quest.completeQuest();

            std::cout << "Iris: Thank you for killing the zombies!" << std::endl;
            std::cout << "Quest Completed!" << std::endl;
        }

        else
        {
            npc->talk();
            std::cout << "Zombies killed: " << storyManager.getZombiesKilled() << "/3" << std::endl;
        }

        return;
    }

    if (npc == &storyManager.getpharmacyNPC())
    {
        Quest& quest = storyManager.getfindPharmacyQuest();

        if (!quest.isAccepted())
        {
            npc->talk();
        }
        else if (hasTemozolomide())
        {
            quest.completeQuest();

            std::cout << "Dr. Chen: You found the Temozolomide!" << std::endl;
            std::cout << "Quest Completed!" << std::endl;
            
            for (int i = 1; i <= player->getItemCount(); i++)
            {
                Item* item = player->getItemByNumber(i);

                if (item != nullptr && item->getName() == "Temozolomide")
                {
                    player->removeItem(item, i);
                    delete item;
                    break;
                }
            }
        }
        else
        {
            npc->talk();
            std::cout << "Dr. Chen: Please bring me the Temozolomide." << std::endl;
        }

        return;
    }
}
