#pragma once
#include "GameObject.h"
#include <string>

class Item : public GameObject
{
public:
	Item(std::string name, std::string description, int x, int y, char symbol);
	
};