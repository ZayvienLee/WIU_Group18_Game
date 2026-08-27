#include "Ranged.h"

Ranged::Ranged()
{
	damageMultiplier = 1;
	isFirearm = false;
}

Ranged::Ranged(std::string n, std::string desc, char sym, int atk, int atkR, int wght, bool isGun, int dmgMulti)
{
	damageMultiplier = dmgMulti;
	isFirearm = isGun;

	Weapon::setDamageMultiplier(damageMultiplier);

	if (isFirearm) {
		Weapon::setDamage(Weapon::getDamage() * Weapon::getDamageMultiplier());
		Weapon::setAtkRange(100);
	}
}

bool Ranged::isGun() const
{
	return isFirearm;
}
