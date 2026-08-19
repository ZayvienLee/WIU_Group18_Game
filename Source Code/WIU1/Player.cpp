#include "Player.h"
#include "Item.h"
#include <string>
#include <iostream>

Player::Player(std::string n, int h, int maxH, int hun, int thi, int capacity)
{
	// GameObject variables
	name = n;
	description = "Description";
	symbol = 'P';

	// Entity variables
	health = h;
	maxHealth = maxH;
	isAlive = true; // Entity is alive by default. Always

	// Player variables
	hunger = hun;
	thirst = thi;
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

void Player::addItem(Item* item)
{
	if (itemCount >= maxItems)
	{
		std::cout << "[INVENTORY FULL] Cannot Pickup Item" << std::endl;
		return;
	}

	// Find the first empty slot
	for (int i = 0; i < maxItems; ++i)
	{
		if (inventory[i] == nullptr)
		{
			inventory[i] = item;
			itemCount++;
			std::cout << "[ADDED] Item to inventory slot " << (i + 1) << std::endl;
			return;
		}
	}

	return;
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
		return inventory[slotNumber];
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
}