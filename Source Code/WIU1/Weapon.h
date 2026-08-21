#pragma once
#include <string>
#include "Item.h"
class Weapon : public Item
{
private:
    int atkRange;
    int dmg;

public:
    Weapon();
    Weapon(std::string, std::string, char, int, int);
};

