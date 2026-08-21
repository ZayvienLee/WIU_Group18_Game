#include <string>
#include "Weapon.h"

// Default values will be assigned to unknown weapon
Weapon::Weapon()
{
	name = "Unknown Weapon Name";
	description = "This weapon has an unknown description";
	symbol = '?';
	atkRange = 0;
	wDamage = 0;
}

Weapon::Weapon(std::string n, std::string desc, char sym, int dmg, int atkR)
{
	// GameObject var

	name = n;
	description = desc;
	symbol = sym;

	// Weapon var

	atkRange = atkR;
	wDamage = dmg;
}

int Weapon::getAtkRange() const
{
	return atkRange;
}

int Weapon::getDamage() const
{
	return wDamage;
}
