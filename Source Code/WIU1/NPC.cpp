#include "NPC.h"
#include "GameObject.h"
#include <iostream>
#include <string>
#include "Quest.h"
 
void NPC::talk() {
    std::cout << name << ": " << dialogue << std::endl;   
    if (quest != nullptr)
    {
        quest->accept();

        std::cout << "Quest: " << quest->getName() << std::endl;
        std::cout << quest->getDescription() << std::endl;
    }
}

Quest* NPC::getQuest() const {
    return quest;
}

NPC::NPC(std::string n, std::string desc, int x, int y, char sym, std::string dial, Quest* qst)
{
    name = n;
    description = desc;
    positionX = x;
    positionY = y;
    symbol = sym;
    dialogue = dial;
    quest = qst;
}