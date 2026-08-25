#include "KeyCard.h"
#include "Player.h"
#include "GameObject.h"
#include <iostream>


KeyCard::KeyCard()
{
	name = "Key Card";
	description = "Grants access to the Safe House.";
	x = -1; y = -1;
	symbol = 'k'; // It is the same colour as knife, but will be of different colour
	inInventory = true;
	weight = 10;
	quantity = 1;
	colourCode = Colour::YELLOW;
}

void KeyCard::consume(Player & player)
{
	std::cout << "[KEY CARD] Just carry this — it unlocks the Safe House door automatically." << std::endl;
}