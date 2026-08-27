#include <string>
#include "GameObject.h"

GameObject::GameObject()
{
	name = "Name";
	description = "Description";
	positionX = 0;
	positionY = 0;
	symbol = '?';
	colourCode = Colour::WHITE;
}

GameObject::GameObject(std::string n, std::string desc, int x, int y, char sym, std::string colour)
{
	name = n;
	description = desc;
	positionX = x;
	positionY = y;
	symbol = sym;
	colourCode = colour;
}

GameObject::~GameObject()
{
	
}

std::string GameObject::getName() const
{
	return name;
}

std::string GameObject::getDescription() const
{
	return description;
}

char GameObject::getSymbol() const
{
	return symbol;
}

std::string GameObject::getColouredSymbol() const
{
	return colourCode + std::string(1, symbol) + Colour::RESET;
}

int GameObject::getX() const
{
	return positionX;
}

int GameObject::getY() const
{
	return positionY;
}