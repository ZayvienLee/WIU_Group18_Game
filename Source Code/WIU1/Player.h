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
		Player(std::string n, std::string desc, char sym, int h, int maxH, int hung, int thir, int atk, bool alive, int capacity); // Overloaded constructor for Player
		~Player(); // Deconstructor to prevent memory leaks

		void syncItemsLocation(int playerLocX, int playerLocY); // Move the items to the player accordingly

		/* Overidden from Entity class */
		void update() override;

		/* Class Specific methods */
		void restoreHunger(int amount);

		/* To manage the Inventory */
		bool addItem(Item* item); // Pick up item when have space. Don't if inventory full.
		void removeItem(Item* item); // Drop item and remove it from the inventory.
		Item* getItemByNumber(int slotNumber); // Get the item based on the number inside the inventory
		void showInventory() const; // Display the Inventory Contents
		int getItemCount() const;
		int getInventoryCapacity() const;

		/* Variable Accessors */
		std::string getName() const;

		/* Outdoor Position Accessors */
		int getOutdoorX() const;
		int getOutdoorY() const;
		void setOutdoorPosition(int x, int y);

		/* Indoor Position Accessors */
		int getIndoorX() const;
		int getIndoorY() const;
		void setIndoorPosition(int x, int y);

		int getHunger() const;
		int getThirst() const;
		void setHunger(int Hunger);
		void setThirst(int Thirst);
};