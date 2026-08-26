#include "Temozolomide.h"
#include "Player.h"
#include <iostream>

Temozolomide::Temozolomide()
{
	name = "Temozolomide";
	description = "A medication needed by Dr. Chen. He urgently needs it.";
	x = 5;
	y = 5;
	symbol = 't';
	inInventory = false;
	weight = 500;
	quantity = 1;
}

void Temozolomide::consume(Player& player)
{
	std::cout << "[TEMOZOLOMIDE] This item is needed by Dr. Chen! You can't consume this item! Bring it to him instead." << std::endl;
}