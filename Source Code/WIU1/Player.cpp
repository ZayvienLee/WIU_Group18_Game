#include "Player.h"
#include "Item.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "Weapon.h"

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
	ammoCount = 0;

	// Set up the coordinates
	outdoorX = 1;
	outdoorY = 1;
	indoorX = 5;
	indoorY = 5;

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

	equippedWeapon = nullptr;
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

	if (equippedWeapon != nullptr)
	{
		delete equippedWeapon;
		equippedWeapon = nullptr;
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
	int arrayIndex = slot - 1;
	if (arrayIndex >= 0 && arrayIndex < maxItems)
	{
		if (inventory[arrayIndex] != nullptr)
		{
			if (inventory[arrayIndex] == item) // Check if the target item what we are looking for
			{
				inventory[arrayIndex] = nullptr; // Set to a null pointer
				itemCount--;
			}
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
		return nullptr;
	}
	return inventory[arrayIndex];
}

// Display Inventory Contents
void Player::showInventory() const
{
	std::cout << std::endl
		<< "========================================" << std::endl
		<< "          PLAYER INVENTORY (" << itemCount << "/" << maxItems << " Slots)" << std::endl
		<< "          Total Weight: " << getTotalWeight() << " g" << std::endl
		<< "========================================" << std::endl;

	if (equippedWeapon != nullptr)
	{
		std::cout << "  Weapon: " << equippedWeapon->getName() << std::endl;
		std::cout << "  Attack Power: " << equippedWeapon->getDamage() << std::endl;
		std::cout << "  Attack Range: " << equippedWeapon->getAtkRange() << std::endl;
		
	}
	else
	{
		std::cout << "  There is no weapon equipped" << std::endl;
	}

	std::cout << "========================================" << std::endl;
	
	if (itemCount == 0)
	{
		std::cout << "  (Your inventory is empty)" << std::endl;
	}
	else
	{
		for (int i = 0; i < maxItems; ++i)
		{
			if (inventory[i] != nullptr)
			{
				// Example:
				// [1] Water ()  (Qty: 5, Wt: 20 g)
				// Helps you to hydrate
				std::cout << "  [" << (i + 1) << "] " << inventory[i]->getName()
					<< " (Qty: " << inventory[i]->getQuantity()
					<< ", Wt: " << (inventory[i]->getWeight() * inventory[i]->getQuantity()) << "g)"
					<< "\n      \"" << inventory[i]->getDescription() << "\"\n";
			}
			else
			{
				std::cout << "  [" << (i + 1) << "] --- Empty ---" << std::endl;
			}
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

int Player::getTotalWeight() const
{
	int total = 0;

	for (int i = 0; i < maxItems; ++i)
	{
		if (inventory[i] != nullptr)
		{
			total += (inventory[i]->getWeight() * inventory[i]->getQuantity());
		}
	}

	return total;
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

int Player::getAmmoCount() const
{
	return ammoCount;
}

Weapon* Player::getWeapon() const
{
	return equippedWeapon;
}

void Player::equipWeapon(Weapon* weapon)
{
	if (weapon == nullptr)
	{
		return;
	}

	if (equippedWeapon != nullptr)
	{
		if (!addItem(equippedWeapon)) {
			std::cout << "[EQUIP] Inventory full / Can't swap weapons." << std::endl;
			return; // abort: keep old weapon equipped, don't touch the new one's caller
		}
	}

	equippedWeapon = weapon;
}

bool Player::unequipWeapon()
{
	if (equippedWeapon == nullptr) {
		return false;
	}
	if (itemCount >= maxItems) {
		return false;
	}

	addItem(equippedWeapon);
	equippedWeapon = nullptr;
	return true;
}

void Player::setHunger(int Hunger)
{
	hunger = std::max(0, std::min(100, Hunger));
}

void Player::setThirst(int Thirst)
{
	thirst = std::max(0, std::min(100, Thirst));
}

void Player::setAmmoCount(int amount)
{
	ammoCount = amount;
}