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
	virtual bool use(Entity* target) = 0;

	int getQuantity() const;
	virtual void consume(Player& player) = 0;

	// Synchronize item position to match player's coordinates
	void syncWithPlayer(int playerX, int playerY);

	void setInInventory(bool status);
	bool getInInventory() const;

	int getX() const;
	int getY() const;
	std::string getName() const;
	void setPosition(int newX, int newY);
};