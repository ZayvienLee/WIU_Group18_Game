#pragma once
#include "GameObject.h"
#include <string>

class Quest  
{
private:
    bool Completed;   
    std::string questName;
    std::string questDescription;

public:
    void completeQuest();
    bool isCompleted() const;
    Quest(const std::string& name, const std::string& description);

    std::string getName() const;
    std::string getDescription() const; 

};
