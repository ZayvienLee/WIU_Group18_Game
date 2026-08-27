#include <string>
#include <iostream>
#include "Weapon.h"
#include "Item.h"
#include "Player.h"
#include "GameObject.h"

// Default values will be assigned to unknown weapon
Weapon::Weapon()
{
	name = "Unknown Weapon";
	description = "This is an Unknown Weapon";
	symbol = '?';

	atkRange = 0;
	wDamage = 0;

	weight = 0;
	colourCode = Colour::MAGENTA;
}

Weapon::Weapon(std::string n, std::string desc, char sym, int atk, int atkR, int wght)
{
	// GameObject var
	name = n;
	description = desc;
	symbol = sym;

	atkRange = atkR;
	wDamage = atk;
	
	weight = wght;
	colourCode = Colour::MAGENTA;
}

void Weapon::consume(Player& player)
{
	// Weapons are meant to be equipped, NOT consumed
	std::cout << "[WEAPON] You can't consume a weapon. Press [U] again to equip it instead." << std::endl;
}

bool Weapon::isConsumable() const
{
	return false;
}

int Weapon::getAtkRange() const
{
	return atkRange;
}

int Weapon::getDamage() const
{
	return wDamage;
}

int Weapon::getWeight() const
{
	return weight;
}

int Weapon::getDamageMultiplier() const
{
	return damageMultiplier;
}

bool Weapon::isTwoHanded() const
{
	return false;
}

bool Weapon::isGun() const
{
	return false;
}

void Weapon::setDamage(int dmg)
{
	wDamage = dmg;
}

void Weapon::setAtkRange(int atkR)
{
	atkRange = atkR;
}

void Weapon::setDamageMultiplier(int dmgMulti)
{
	damageMultiplier = dmgMulti;
}
