#include <iostream>
#include "KeyCard.h"
#include "Player.h"
#include "GameObject.h"

KeyCard::KeyCard()
{
	name = "Key Card";
	description = "Grants access to the Safe House.";
	x = -1; y = -1;
	symbol = 'k'; // It is the same symbol as knife, but will be of different colour
	inInventory = true;
	weight = 50;
	quantity = 1;
	colourCode = Colour::BOLD_CYAN;
}

void KeyCard::consume(Player & player)
{
	std::cout << "[KEY CARD] Just carry this — it unlocks the Safe House door automatically." << std::endl;
}

bool KeyCard::isConsumable() const
{
	return false;
}
