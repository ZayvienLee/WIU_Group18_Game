#include <string>
#include <iostream>
#include "Weapon.h"
#include "Item.h"
#include "Player.h"

// Default values will be assigned to unknown weapon
Weapon::Weapon()
{
	name = "Unknown Weapon";
	description = "This is an Unknown Weapon";
	symbol = '?';
	atkRange = 1;
	wDamage = 0;
	weight = 0;
}

Weapon::Weapon(std::string n, std::string desc, char sym, int atk, int atkR, int wght)
{
	// GameObject var
	name = n;
	description = desc;
	symbol = sym;

	atkRange = atkR;
	wDamage = atk;
	weight = wght;
}

void Weapon::consume(Player& player)
{
	// Weapons are meant to be equipped, NOT consumed
	std::cout << "[WEAPON] You can't consume a weapon. Press [U] again to equip it instead." << std::endl;
}

int Weapon::getAtkRange() const
{
	return atkRange;
}

int Weapon::getDamage() const
{
	return wDamage;
}