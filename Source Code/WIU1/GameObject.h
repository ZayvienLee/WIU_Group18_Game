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
		GameObject(const std::string& name, const std::string& description, int x, int y, char symbol);
};