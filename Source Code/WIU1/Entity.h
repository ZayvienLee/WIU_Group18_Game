#pragma once
#include "GameObject.h"

class Entity : public GameObject
{
	protected:
		int health;
		int maxHealth;
		int attackPower;
		bool isAlive;
		int test;
};