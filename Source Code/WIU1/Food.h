#pragma once
#include "Item.h"
#include "Player.h"

class Food : public Item
{
private:
	int foodPt;

public:
	Food();

	void consume(Player& player) override;
};