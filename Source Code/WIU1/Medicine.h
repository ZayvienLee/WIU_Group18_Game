#pragma once
#include "Item.h"
#include "Player.h"

class Medicine : public Item
{
private:
	int recoverHp;

public:
	Medicine();

	void consume(Player& player) override;
};