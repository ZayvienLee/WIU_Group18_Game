#pragma once
#include "Item.h"
#include "Player.h"

class Ammunition : public Item
{
public:
	Ammunition();

	void consume(Player& player) override;
};