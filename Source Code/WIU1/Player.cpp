#include "Player.h"
#include "Item.h"
#include <string>
#include <iostream>
#include <algorithm>

Player::Player(std::string n, std::string desc, char sym, int h, int maxH, int hung, int thir, int atk, bool alive, int capacity)
{
	// GameObject variables
	name = n;
	description = desc;
	symbol = sym;

	// Entity variables
	health = h;
	maxHealth = maxH;
	attackPower = atk;
	isAlive = alive; // Entity is alive by default. Always

	// Player variables
	hunger = hung;
	thirst = thir;
	maxItems = capacity;
	itemCount = 0;

	// Set up the coordinates
	outdoorX = 1;
	outdoorY = 1;
	indoorX = 0;
	indoorY = 0;

	// Inventory system
	if (maxItems <= 0) // Should the number be not a positive number, set to default accordingly
	{
		maxItems = 10;
	}

	// Allocation of the array pointer
	inventory = new Item * [maxItems];
	for (int i = 0; i < maxItems; ++i)
	{
		inventory[i] = nullptr;
	}
}

Player::~Player()
{
	if (inventory != nullptr)
	{
		for (int i = 0; i < maxItems; ++i)
		{
			// Delete each item object inside the inventory
			if (inventory[i] != nullptr)
			{
				delete inventory[i];
				inventory[i] = nullptr;
			}
		}

		// Delete the inventory array
		delete[] inventory;
		inventory = nullptr;
	}
}

void Player::syncItemsLocation(int playerLocX, int playerLocY)
{
	// Keep item positions synchronized with player coordinates in background
	for (int i = 0; i < maxItems; ++i) {
		if (inventory[i] != nullptr) {
			inventory[i]->syncWithPlayer(playerLocX, playerLocY);
		}
	}
}

void Player::update()
{
	// Player turn logic: decrease hunger/thirst every step
	hunger = std::max(0, hunger - 1);
	thirst = std::max(0, thirst - 2);
}

void Player::restoreHunger(int amount)
{
	hunger = std::min(100, hunger + amount);
	std::cout << name << " restored " << amount << " Hunger!" << std::endl;
}

bool Player::addItem(Item* item)
{
	if (itemCount >= maxItems)
	{
		return false;
	}

	// Find the first empty slot
	for (int i = 0; i < maxItems; ++i)
	{
		if (inventory[i] == nullptr)
		{
			inventory[i] = item;
			itemCount++;

			return true;
		}
	}

	return false;
}

void Player::removeItem(Item* item, int slot)
{
	if (inventory[slot] != nullptr)
	{
		if (inventory[slot] == item) // Check if the target item what we are looking for
		{
			inventory[slot] = nullptr; // Set to a null pointer
			itemCount--;
		}
	}
}

// Get Item Pointer based on User Number Input (1-indexed selection)
Item* Player::getItemByNumber(int slotNumber)
{
	int arrayIndex = slotNumber - 1; // Set the number to the 0-based index

	// Check the bounds and Null pointer
	if (arrayIndex < 0 || arrayIndex >= maxItems)
	{
		std::cout << "Invalid Slot. Slot " << slotNumber << " is NOT a valid inventory slot number! Try Again." << std::endl;
		return nullptr;
	}
	else if (inventory[arrayIndex] == nullptr)
	{
		std::cout << "[NO ITEM] No item exists at slot " << slotNumber << ". Try Again." << std::endl;
		return nullptr;
	}
	else
	{
		return inventory[arrayIndex];
	}
}

// Display Inventory Contents
void Player::showInventory() const
{
	std::cout
		<< std::endl << "========================================" << std::endl
		<< "          PLAYER INVENTORY (" << itemCount << "/" << maxItems << ")" << std::endl
		<< "========================================" << std::endl;

	if (itemCount == 0)
	{
		std::cout << "  (Your inventory is currently empty)" << std::endl;
	}
	else
	{
		for (int i = 0; i < maxItems; ++i)
		{
			if (inventory[i] != nullptr) {
				std::cout << "  [" << (i + 1) << "] " << "Name of Item"
					<< " (Qty: " << "Quantity of item" << ")" << std::endl;;
			}
			else {
				std::cout << "  [" << (i + 1) << "] --- Empty ---" << std::endl;
			}

			/*
			if (inventory[i] != nullptr) {
				std::cout << "  [" << (i + 1) << "] " << inventory[i]->getName()
					<< " (Qty: " << inventory[i]->getQuantity() << ")\n";
			}
			else {
				std::cout << "  [" << (i + 1) << "] --- Empty ---\n";
			}
			*/
		}
	}

	std::cout << "========================================" << std::endl;
}

int Player::getItemCount() const
{
	return itemCount;
}

int Player::getInventoryCapacity() const
{
	return maxItems;
}

std::string Player::getName() const
{
	return name;
}

int Player::getOutdoorX() const
{
	return outdoorX;
}

int Player::getOutdoorY() const
{
	return outdoorY;
}

void Player::setOutdoorPosition(int x, int y)
{
	outdoorX = x;
	outdoorY = y;

	syncItemsLocation(outdoorX, outdoorY); // Syncronise the location of the items to the player's location.
}

int Player::getIndoorX() const
{
	return indoorX;
}

int Player::getIndoorY() const
{
	return indoorY;
}

void Player::setIndoorPosition(int x, int y)
{
	indoorX = x;
	indoorY = y;

	syncItemsLocation(indoorX, indoorY); // Syncronise the location of the items to the player's location.
}

int Player::getHunger() const
{
	return hunger;
}

int Player::getThirst() const
{
	return thirst;
}
