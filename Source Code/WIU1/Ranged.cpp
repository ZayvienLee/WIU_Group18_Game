#include "Ranged.h"
#include "Weapon.h"
#include <string>

Ranged::Ranged() : Weapon() // inherits all of Weapon's defaults
{
	isFirearm = false;
}

Ranged::Ranged(std::string n, std::string desc, char sym, int atk, int atkR, int wght, bool isGun, int dmgMulti)
	: Weapon(n, desc, sym, atk, atkR, wght)
{
	isFirearm = isGun;
	setDamageMultiplier(dmgMulti);

	if (isFirearm)
	{
		setDamage(getDamage() * dmgMulti);

		// Minimum reach of FireArms
		if (getAtkRange() < 6)
		{
			setAtkRange(6);
		}
	}
}

bool Ranged::isGun() const
{
	return isFirearm;
}