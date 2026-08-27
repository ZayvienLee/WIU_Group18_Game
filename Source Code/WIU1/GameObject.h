#pragma once
#include <string>

// Colours via ANSI Escape Codes are defined in the namespace below
// To differntiate the different objects in the game
namespace Colour
{
	inline constexpr char RESET[] = "\033[0m";
	inline constexpr char RED[] = "\033[31m";
	inline constexpr char GREEN[] = "\033[32m";
	inline constexpr char YELLOW[] = "\033[33m";
	inline constexpr char BLUE[] = "\033[34m";
	inline constexpr char MAGENTA[] = "\033[35m";
	inline constexpr char CYAN[] = "\033[36m";
	inline constexpr char WHITE[] = "\033[37m";
	inline constexpr char BOLD_RED[] = "\033[1;31m";
	inline constexpr char BOLD_GREEN[] = "\033[1;32m";
	inline constexpr char BOLD_YELLOW[] = "\033[1;33m";
	inline constexpr char BOLD_BLUE[] = "\033[1;34m";
	inline constexpr char BOLD_MAGENTA[] = "\033[1;35m";
	inline constexpr char BOLD_CYAN[] = "\033[1;36m";
	inline constexpr char BOLD_WHITE[] = "\033[1;37m";
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
	virtual ~GameObject();

	/* Accessor Functions */
	std::string getName() const;
	std::string getDescription() const;
	char getSymbol() const;
	std::string getColouredSymbol() const;

	int getX() const;
	int getY() const;
};