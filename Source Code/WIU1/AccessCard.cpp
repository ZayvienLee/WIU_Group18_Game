#include <iostream>
#include "AccessCard.h"
#include "Player.h"
#include "GameObject.h"

AccessCard::AccessCard()
{
	name = "Access Card";
	description = "Clearance Card to allow you entrance to Haven-7!";
	x = -1; y = -1;
	symbol = 'a'; // A similar symbol, but will be of different colour
	inInventory = true;
	weight = 50;
	quantity = 1;
	colourCode = Colour::BOLD_CYAN;
}

void AccessCard::consume(Player & player)
{
	std::cout << "[ACCESS CARD] Just carry this - it is the key to salvation and freedom!" << std::endl;
}

bool AccessCard::isConsumable() const
{
	return false;
}
