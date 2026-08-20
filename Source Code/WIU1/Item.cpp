#include <vector>
#include "Item.h"
#include <string>
#include "Player.h"

Item::Item()
{
	name = "Item Name";
	description = "Item Description";
	x = -1;
	y = -1;
	symbol = '?';
	inInventory = false;
	weight = 0;
	quantity = 0;
}

Item::Item(std::string n, std::string desc, int xPos, int yPos, char sym, int wght, int qty, bool inInvent)
{
	name = n;
	description = desc;
	x = xPos;
	y = yPos;
	symbol = sym;
	inInventory = inInvent;
	weight = wght;
	quantity = qty;
}

int Item::getQuantity() const
{
	return quantity;
}

void Item::syncWithPlayer(int playerX, int playerY)
{
	x = playerX;
	y = playerY;
}

void Item::setInInventory(bool status)
{
	inInventory = status;
}

bool Item::getInInventory() const
{
	return inInventory;
}

int Item::getX() const
{
	return x;
}

int Item::getY() const
{
	return y;
}

std::string Item::getName() const
{
	return name;
}

void Item::setPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}