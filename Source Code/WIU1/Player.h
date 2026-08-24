#pragma once
#include "Entity.h"
#include "Item.h"
#include <string>

class Weapon; // Forward declaration to avoid circular include

class Player : public Entity
{
	private:
		int hunger; // Affected by the action the player takes, starts losing health when critically low
		int thirst; // How hydrated the player is. Affected by the action the player takes, starts losing health when critically low
		int ammoCount; // Number of bullets that the player has

		// Inventory system to hold the items
		Item** inventory; // Dynamically allocate array of Item pointer as inventory
		Weapon* equippedWeapon; // This pointer is what the player equips
		int maxItems; // The maximum number of items that the player can carry
		int itemCount; // The current number of items held

		/* The coordinates for the player */
		int outdoorX, outdoorY;
		int indoorX, indoorY;

	public:
		Player(std::string n, std::string desc, char sym, int h, int maxH, int hung, int thir, int atk, bool alive, int capacity); // Overloaded constructor for Player
		~Player(); // Deconstructor to prevent memory leaks

		void syncItemsLocation(int playerLocX, int playerLocY); // Move the items to the player accordingly
		void update() override; /* Overidden from Entity class */

		/* To manage the Inventory */
		bool addItem(Item* item); // Pick up item when have space. Don't if inventory full.
		void removeItem(Item* item, int slot); // Drop item and remove it from the inventory.
		Item* getItemByNumber(int slotNumber); // Get the item based on the number inside the inventory
		void showInventory() const; // Display the Inventory Contents
		
		/* Variable Accessors */
		int getItemCount() const;
		int getInventoryCapacity() const;
		int getTotalWeight() const;
		std::string getName() const;
		int getOutdoorX() const;
		int getOutdoorY() const;
		void setOutdoorPosition(int x, int y);
		int getIndoorX() const;
		int getIndoorY() const;
		void setIndoorPosition(int x, int y);
		int getHunger() const;
		int getThirst() const;
		int getAmmoCount() const;
		Weapon* getWeapon() const;

		/* Set the data of the variables */
		void equipWeapon(Weapon* weapon);
		bool unequipWeapon();
		void setHunger(int Hunger);
		void setThirst(int Thirst);
		void setAmmoCount(int amount);
};