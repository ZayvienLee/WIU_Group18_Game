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
    Entity();
    Entity(std::string n, std::string desc, int x, int y, char sym, int h, int maxH, int atk, bool alive);

    // VIrtual deconstructor
    virtual ~Entity() = default;

    // Pure virtual function. Each child should define its turn behaviour
    virtual void update() = 0;


    // Common shared Functions
    virtual void takeDamage(int damage);

    void heal(int amount);


    // Accessory Functions
    bool getIsAlive() const;
    int getHealth() const;
    void setHealth(int Health);
};