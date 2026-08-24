#pragma once
#include <string>
#include "Item.h"

class Player; // Forward declaration to avoid circular include

class Weapon : public Item
{
private:
    int atkRange;
    int wDamage;

public:
    Weapon();
    Weapon(std::string n, std::string desc, char sym, int atk, int atkR);

    void consume(Player& player) override;

	int getDamage() const;
	int getAtkRange() const;
};

