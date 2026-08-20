#pragma once
#include "GameObject.h"
#include "Player.h"
#include <string>

class Item : public GameObject
{
public:
	Item(std::string name, std::string description, int x, int y, char symbol);
	
	virtual void Consume(Player& player);
};