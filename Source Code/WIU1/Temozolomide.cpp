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
	weight = 1;
	quantity = 1;
}

void Temozolomide::consume(Player& player)
{

}