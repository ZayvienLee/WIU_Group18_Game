#pragma once
#include "Item.h"

class Player;

class KeyCard : public Item
{
public:
	KeyCard();
	void consume(Player& player) override;
	bool isConsumable() const override;
};