#include "Temozolomide.h"
#include <iostream>

Temozolomide::Temozolomide()
{
	name = "Temozolomide";
	description = "A medication needed by Dr. Chen.";
	x = 5;
	y = 5;
	symbol = 'o';
	inInventory = false;
	weight = 1;
	quantity = 1;
}

void Temozolomide::consume(Player& player)
{
}


