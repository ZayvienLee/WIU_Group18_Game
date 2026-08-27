#pragma once
#include "Weapon.h"
class Ranged : public Weapon
{
private:
	int damageMultiplier;
	bool isFirearm; // Indicates if the ranged weapon is a firearm

public:
	Ranged();
	Ranged(std::string n, std::string desc, char sym, int atk, int atkR, int wght, bool isGun, int dmgMulti);

	bool isGun() const override;
};

