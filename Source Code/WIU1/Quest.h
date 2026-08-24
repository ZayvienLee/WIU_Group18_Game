#pragma once
#include "GameObject.h"
#include <string>

class Quest  
{
private:
    bool Completed;   
    bool accepted;
    std::string questName;
    std::string questDescription;


public:
    void completeQuest();
    bool isCompleted() const;
    Quest(std::string name, std::string description);

    void accept();
    bool isAccepted() const;

    std::string getName() const;
    std::string getDescription() const; 

};

