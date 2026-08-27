#include <string>
#include <iostream>
#include "QuestItem.h"
#include "Player.h"
#include "GameObject.h"

QuestItem::QuestItem()
{
	name = "Quest Item";
	description = "This item is related to a Quest";
	x = -1; y = -1;
	symbol = '?';
	inInventory = true;
	weight = 100;
	quantity = 1;
	colourCode = Colour::BOLD_MAGENTA;
}

QuestItem::QuestItem(std::string n, std::string desc, char sym)
{
	name = n;
	description = desc;
	x = -1; y = -1;
	symbol = sym;
	inInventory = true;
	weight = 100;
	quantity = 1;
	colourCode = Colour::BOLD_MAGENTA;
}

void QuestItem::consume(Player & player)
{
	std::cout << "[QUEST ITEM] This can't be used directly - bring it to whoever needs it." << std::endl;
}

bool QuestItem::isConsumable() const
{
	return false;
}
