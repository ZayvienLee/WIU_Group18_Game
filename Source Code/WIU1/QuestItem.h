#pragma once
#include "Item.h"
#include <string>

class QuestItem : public Item
{
public:
	QuestItem();
	QuestItem(std::string n, std::string desc, char sym);
	void consume(Player& player) override;
};