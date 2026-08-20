#include "GameObject.h"
#include <string>

GameObject::GameObject()
{
	name = "Name";
	description = "Description";
	positionX = 0;
	positionY = 0;
	symbol = '?';
}

GameObject::GameObject(std::string n, std::string desc, int x, int y, char sym)
{
	name = n;
	description = desc;
	positionX = x;
	positionY = y;
	symbol = sym;
}

std::string GameObject::getName()
{
	return name;
}

char GameObject::getSymbol()
{
	return symbol;
}
