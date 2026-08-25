#pragma once
#include <string>

// Colours via ANSI Escape Codes are defined in the namespace below
// To differntiate the different objects in the game
namespace Colour
{
	const std::string RESET = "\033[0m";
	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string BLUE = "\033[34m";
	const std::string MAGENTA = "\033[35m";
	const std::string CYAN = "\033[36m";
	const std::string BOLD_CYAN = "\033[1;36m";
	const std::string WHITE = "\033[37m";
	const std::string BOLD_RED = "\033[1;31m";
}

class GameObject
{
protected:
	std::string name;
	std::string description;
	int positionX;
	int positionY;
	char symbol;
	std::string colourCode; // This is used to differentiate the objects in the game by their colour, in addition to symbol

public:
	GameObject();
	GameObject(std::string n, std::string desc, int x, int y, char sym, std::string colour = Colour::WHITE);

	/* Accessor Functions */
	std::string getName() const;
	char getSymbol() const;
	std::string getColouredSymbol() const;

	int getX() const;
	int getY() const;
};