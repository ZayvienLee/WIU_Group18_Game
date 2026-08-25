#pragma once
#include "GameObject.h"
#include "Quest.h"
#include <string>

class NPC :
    public GameObject
{
private:
    std::string dialogue; // This dialogue plays when the player first interacts with the NPC
    std::string dialogueProgress; // The NPC reminds the player that they still have to complete the quest
    std::string dialogueComplete; // The NPC thanks the player for helping them out
    Quest* quest;
 
public:
    NPC(std::string n, std::string desc, int x, int y, char sym, Quest* qst, std::string dial, std::string dialProgress = "?", std::string dialComplete = "?");
    void talk();
    Quest* getQuest() const;

};

