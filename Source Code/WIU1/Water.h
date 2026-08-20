#pragma once
#include "Item.h"
#include "Player.h"

class Water : public Item
{
private:
	int waterPt;

public:
	Water();

	void consume(Player& player) override;
};