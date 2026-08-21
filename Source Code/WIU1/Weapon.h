#pragma once
#include <string>
#include "Item.h"

class Weapon : public Item
{
private:
    int atkRange;
    int wDamage;

public:
    Weapon();
    Weapon(std::string n, std::string desc, char sym, int atk, int atkR);

	int getDamage() const;
	int getAtkRange() const;
};

