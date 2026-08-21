#include <string>
#include "Weapon.h"

Weapon::Weapon()
{
	name = "Unknown Weapon";
	description = "This is an Unknown Weapon";
	symbol = '?';
	atkRange = 1;
	dmg = 0;
}

Weapon::Weapon(std::string n, std::string desc, char sym, int atk, int atkR)
{
	// GameObject var

	name = n;
	description = desc;
	symbol = sym;

	atkRange = atkR;
	dmg = atk;
}
