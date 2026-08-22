#pragma once
#include "Item.h"

class Ammunition : public Item
{
public:
	void consume(Player& player) override;
};