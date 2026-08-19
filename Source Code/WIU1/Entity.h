#pragma once
#include "GameObject.h"
#include <string>

class Entity : public GameObject
{
protected:
    int health;
    int maxHealth;
    int attackPower;
    bool isAlive;

public:
};