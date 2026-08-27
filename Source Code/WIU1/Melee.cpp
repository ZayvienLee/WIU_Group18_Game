#include "Melee.h"
#include "Weapon.h"
#include <string>

Melee::Melee() : Weapon() // inherits all of Weapon's defaults
{
	is2Handed = false;
}

Melee::Melee(std::string n, std::string desc, char sym, int atk, int atkR, int wght, bool in2Hands, int dmgMulti)
	: Weapon(n, desc, sym, atk, atkR, wght) // delegate: sets weight, name, damage, range, etc.
{
	is2Handed = in2Hands;
	setDamageMultiplier(dmgMulti);

	// Two-handed weapons swing harder, multiplies the damage
	if (is2Handed)
	{
		setDamage(getDamage() * dmgMulti);
	}
}

bool Melee::isTwoHanded() const
{
	return is2Handed;
}