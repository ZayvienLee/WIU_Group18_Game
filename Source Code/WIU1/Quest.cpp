#include <string>
#include <iostream>
#include "Quest.h"

Quest::Quest()
{
    Completed = false;
    questName = "Unknown Quest";
    questDescription = "There is nothing to do.";
    accepted = false;
}

Quest::Quest(std::string name, std::string description)
{
    Completed = false;
    questName = name;
    questDescription = description;
    accepted = false;
}

void Quest::completeQuest() {

    std::cout << "Quest Completed!" << std::endl;

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

void Quest::accept()
{
    accepted = true;
}

bool Quest::isAccepted() const
{
    return accepted;
}


