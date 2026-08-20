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
    NPC(std::string n, std::string desc, int x, int y, char sym, std::string dial, Quest* qst);
    void talk();
    Quest* getQuest() const;

};

