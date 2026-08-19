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
    NPC(const std::string& name, const std::string& description, int x, int y, char symbol, const std::string& dialogue, Quest* quest);
    void talk();
    Quest* getQuest() const;

};

