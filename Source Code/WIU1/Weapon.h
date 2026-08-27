#pragma once
#include <string>
#include "Item.h"

class Player; // Forward declaration to avoid circular include

class Weapon : public Item
{
private:
    int atkRange;
    int wDamage;
	int damageMultiplier; // Multiplier for damage if the weapon is two-handed

public:
    Weapon();
    Weapon(std::string n, std::string desc, char sym, int atk, int atkR, int wght);

    void consume(Player& player) override;

    bool isConsumable() const override;

	void setDamage(int dmg);
	void setAtkRange(int atkR);
	void setDamageMultiplier(int dmgMulti);

	int getDamage() const;
	int getAtkRange() const;
	int getWeight() const;
	int getDamageMultiplier() const;

	virtual bool isTwoHanded() const;
	virtual bool isGun() const;
};

