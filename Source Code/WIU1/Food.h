#pragma once
#include "Item.h"

class Food : public Item
{
private:
	int foodPt;

public:
	Food();

	void Consume(Player& player) override;
};