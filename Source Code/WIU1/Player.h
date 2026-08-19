#pragma once
#include "Entity.h"
#include "Item.h"
#include <string>

class Player : public Entity
{
	private:
		int hunger; // Affected by the action the player takes, starts losing health when critically low
		int thirst; // How hydrated the player is. Affected by the action the player takes, starts losing health when critically low

		// Inventory system to hold the items
		Item** inventory; // Dynamically allocate array of  Item pointer
		int maxItems; // The maximum number of items that the player can carry
		int itemCount; // The current number of items held

		/* The coordinates for the player */
		int outdoorX, outdoorY;
		int indoorX, indoorY;

	public:
		Player(std::string n, int h, int maxH, int hun, int thi, int capacity); // Overloaded constructor for Player
		~Player(); // Deconstructor to prevent memory leaks

		/* To manage the Inventory */
		void addItem(Item* item); // Pick up item when have space. Don't if inventory full.
		Item* getItemByNumber(int slotNumber); // Get the item based on the number inside the inventory
		void showInventory() const; // Display the Inventory Contents

		int getItemCount() const;
		int getInventoryCapacity() const;

		/* Outdoor Position Accessors */
		int getOutdoorX() const;
		int getOutdoorY() const;
		void setOutdoorPosition(int x, int y);

		/* Indoor Position Accessors */
		int getIndoorX() const;
		int getIndoorY() const;
		void setIndoorPosition(int x, int y);
};