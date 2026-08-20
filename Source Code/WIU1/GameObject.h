#pragma once
#include <string>

class GameObject
{
protected:
	std::string name;
	std::string description;
	int positionX;
	int positionY;
	char symbol;
public:
	GameObject();
	GameObject(std::string n, std::string desc, int x, int y, char sym);

	/* Accessor Functions */
	std::string getName() const;
	char getSymbol() const;
};