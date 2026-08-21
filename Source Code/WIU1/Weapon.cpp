#include <string>
#include "Weapon.h"

Weapon::Weapon(std::string n, std::string desc, char sym, int atk, int atkRange
{
	// GameObject var

	name = n;
	description = desc;
	symbol = sym;

	atkRange = atkRange;
	dmg = atk;
}
