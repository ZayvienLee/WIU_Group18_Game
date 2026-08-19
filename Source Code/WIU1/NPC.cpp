#include "NPC.h"
#include <iostream>
 
void NPC::talk() {
    std::cout << name << ": " << dialogue << std::endl;   
    if (quest != nullptr) {
        if (!quest ->isCompleted()) {
            std::cout << "Quest: " << quest->getName() << std::endl;
            std::cout << quest->getDescription() << std::endl;
        }
        else {
            std::cout << "Quest Completed!" << std::endl;
        }
    }
}

Quest* NPC::getQuest() const {
    return quest;
}
NPC::NPC(const std::string& name, const std::string& description, int x, int y, char symbol, const std::string& dialogue, Quest* quest)
    : GameObject(name, description, x, y, symbol), dialogue(dialogue), quest(quest) {
}
