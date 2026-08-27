#include <iostream>
#include <string>
#include "NPC.h"
#include "GameObject.h"
#include "Quest.h"

NPC::NPC(std::string n, std::string desc, int x, int y, char sym, Quest* qst, std::string dial, std::string dialProgress, std::string dialComplete)
{
    name = n;
    description = desc;
    positionX = x;
    positionY = y;
    symbol = sym;
    quest = qst;
    colourCode = Colour::CYAN;

    // Dialogue to convey to player
    dialogue = dial;
    dialogueProgress = dialProgress;
    dialogueComplete = dialComplete;
}

NPC::~NPC()
{

}

void NPC::talk()
{  
    if (quest != nullptr)
    {   
        if (quest->isAccepted()) {
            if (!quest->isCompleted()) {
                std::cout << name << ": " << dialogueProgress << std::endl;
            }
            else {
                std::cout << name << ": " << dialogueComplete << std::endl;
            }
        }
        else {
            quest->accept();

            std::cout << name << ": " << dialogue << std::endl;
            std::cout << "[QUEST ACCEPTED] " << quest->getName() << std::endl;
            std::cout << "Description (How to Complete): " << quest->getDescription() << std::endl;
        }
    }
    else {
        if (name == "Timothy") {
            std::cout << name << ": " << dialogue << std::endl;
        }
    }
}

void NPC::setPosition(int newX, int newY)
{
    positionX = newX;
    positionY = newY;
}

Quest* NPC::getQuest() const
{
    return quest;
}