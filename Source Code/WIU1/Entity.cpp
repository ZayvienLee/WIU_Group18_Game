#include "Entity.h"
#include <string>
#include <iostream>
#include <algorithm>

// Default values will be assigned to unknown entity
Entity::Entity()
{
	name = "Unknown Entity Name";
	description = "This entity has an unknown description";
	positionX = 0;
	positionY = 0;
	symbol = '?';
	health = 20;
	maxHealth = 20;
	attackPower = 5;
	isAlive = true;
}

Entity::Entity(std::string n, std::string desc, int x, int y, char sym, int h, int maxH, int atk, bool alive)
{
	name = n;
	description = desc;
	positionX = x;
	positionY = y;
	symbol = sym;
	health = h;
	maxHealth = maxH;
	attackPower = atk;
	isAlive = alive;
}

void Entity::takeDamage(int damage)
{
	health -= damage;
	std::cout << name << " took " << damage << " damage! (HP: " << health << "/" << maxHealth << ")" << std::endl;
	
	if (health <= 0)
	{
		health = 0;
		isAlive = false;
		std::cout << name << " has died." << std::endl;
	}
}

void Entity::heal(int amount)
{
	health = std::min(maxHealth, health + amount);
	std::cout << name << " restored " << amount << " HP! (HP: " << health << "/" << maxHealth << ")" << std::endl;
}

bool Entity::getIsAlive() const
{
	return isAlive;
}

int Entity::getHealth() const
{
	return health;
}

void Entity::setHealth(int Health)
{
	health = Health;
}

