#include "GameObject.h"
#include <string>

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

std::string GameObject::getName() const
{
	return name;
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