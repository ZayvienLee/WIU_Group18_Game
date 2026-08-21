#include "Quest.h"
#include <string>


void Quest::completeQuest() {
    Completed = true;
}

bool Quest::isCompleted() const {
    return Completed; 
}

std::string Quest::getName() const {
    return questName;
}

std::string Quest::getDescription() const {
    return questDescription;
}

Quest::Quest(std::string name, std::string description) : Completed(false), questName(name), questDescription(description)
{

}
