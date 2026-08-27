#pragma once
#include "Weapon.h"
class Melee : public Weapon
{
private:
	int damageMultiplier; // Multiplier for damage if the melee weapon is two-handed
	bool is2Handed; // Indicates if the melee weapon requires two hands to wield

public:
	Melee();
	Melee(std::string n, std::string desc, char sym, int atk, int atkR, int wght, bool in2Hands, int dmgMulti);

	bool isTwoHanded() const override;
};

