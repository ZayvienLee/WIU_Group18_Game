#pragma once
#include "GameObject.h"
#include <string>

class Entity; /* Forward declaration to avoid circular include */
class Player; /* Forward declaration to avoid circular include */

class Item : public GameObject
{
protected:
	int x, y;
	bool inInventory;
	int weight;
	int quantity;

public:
	Item();
	Item(std::string n, std::string desc, int xPos, int yPos, char sym, int wght, int qty, bool inInvent = false);

	virtual ~Item() = default;

	// Pure Virtual Function: Every Item type MUST define what happens when used
	virtual void consume(Player& player) = 0;
	virtual bool isConsumable() const;

	int getQuantity() const;
	void setQuantity(int qty);
	int getWeight() const;
	std::string getDescription() const;

	void syncWithPlayer(int playerX, int playerY);// Synchronize item position to match player's coordinates
	void setInInventory(bool status);
	bool getInInventory() const;

	int getX() const;
	int getY() const;
	std::string getName() const;
	void setPosition(int newX, int newY);
};