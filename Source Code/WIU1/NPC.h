#pragma once
#include "GameObject.h"
#include "Quest.h"
#include <string>

class NPC :
    public GameObject
{
private:
    std::string dialogue;
    Quest* quest;  
 
public:
    NPC(std::string name, std::string description, int x, int y, char symbol, std::string dialogue, Quest* quest);
    void talk();
    Quest* getQuest() const;

};

