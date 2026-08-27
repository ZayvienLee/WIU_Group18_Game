#include "Melee.h"
#include "Player.h"

Melee::Melee()
{
	damageMultiplier = 1;
	is2Handed = false;
}

Melee::Melee(std::string n, std::string desc, char sym, int atk, int atkR, int wght, bool in2Hands, int dmgMulti)
{
	damageMultiplier = dmgMulti;
	is2Handed = in2Hands;

	Weapon::setDamageMultiplier(damageMultiplier);

	if (is2Handed) {
		Weapon::setDamage(Weapon::getDamage() * Weapon::getDamageMultiplier());
	}
}

bool Melee::isTwoHanded() const
{
	return is2Handed;
}