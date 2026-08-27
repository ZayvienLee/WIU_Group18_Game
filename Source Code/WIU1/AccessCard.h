#pragma once
#include "Item.h"

class Player;

class AccessCard : public Item
{
public:
	AccessCard();
	void consume(Player& player) override;
	bool isConsumable() const override;
};