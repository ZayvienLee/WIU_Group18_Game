#include <string>
#include "Weapon.h"

// Default values will be assigned to unknown weapon
Weapon::Weapon()
{
	name = "Unknown Weapon";
	description = "This is an Unknown Weapon";
	symbol = '?';
	atkRange = 1;
	wDamage = 0;
}

Weapon::Weapon(std::string n, std::string desc, char sym, int atk, int atkR)
{
	// GameObject var
	name = n;
	description = desc;
	symbol = sym;

	atkRange = atkR;
	wDamage = atk;
}

int Weapon::getAtkRange() const
{
	return atkRange;
}

int Weapon::getDamage() const
{
	return wDamage;
}