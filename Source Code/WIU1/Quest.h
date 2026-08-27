#pragma once
#include <string>

class Quest  
{
private:
    bool Completed;   
    bool accepted;
    std::string questName;
    std::string questDescription;


public:
    Quest();
    Quest(std::string name, std::string description);

    void completeQuest();
    bool isCompleted() const;

    void accept();
    bool isAccepted() const;

    std::string getName() const;
    std::string getDescription() const; 

};

