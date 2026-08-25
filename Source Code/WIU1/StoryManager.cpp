#include "StoryManager.h"
#include <cstdlib>
#include <iostream>
#include "NPC.h"
#include "Quest.h"
#include <string>

constexpr auto RESET = "\033[37m";
constexpr auto RED = "\033[31m";    /* Red */
constexpr auto GREEN = "\033[32m";  /* Green */

void StoryManager::storyIntro() {

    std::cout << "Three weeks ago, a mysterious virus spread across the city." << std::endl;
    std::cout << "At first, infected people became extremely aggressive. Within hours, hospitals were overwhelmed. The government declared an emergency and ordered everyone to remain indoors." << std::endl;
    std::cout << "Then the power went out." << std::endl;
    std::cout << "The military abandoned the city." << std::endl;
    std::cout << "The internet disappeared" << std::endl;
    std::cout << "And the dead started walking" << std::endl;
    std::cout << "You play as Alex, a survivor trapped inside an apartment building with only a small amount of food and water." << std::endl;
    std::cout << "One night, your radio suddenly turns on" << std::endl;
    std::cout << "\033[1mThis is Haven-7. We have survivors. We have medicine. We are leaving the city in 48 hours." << std::endl;
    std::cout << "\033[0mThen the transmission cuts out" << std::endl;
    std::cout << "You have two days to reach Haven-7" << std::endl;
    std::cout << "But there is one problem." << std::endl;
    std::cout << "\033[1mHaven-7 is on the other side of the city.\033[0m" << std::endl;
    
}

int StoryManager::GetTimeToNextEvent() const
{
    return TimeToNextEvent;
}

int StoryManager::GetMessageRand() const
{
    return MessageRand;
}

void StoryManager::SetTimeToNextEvent()
{
    TimeToNextEvent = (rand() % 121) + 60;
}

void StoryManager::SetMessageRand()
{
    MessageRand = rand() % 5;
}

void StoryManager::RadioMessage()
{
    if (MessageRand == 0)
    {
        std::cout << "*Unintelligible Noises*" << std::endl;
    }
    else if (MessageRand == 1)
    {
        std::cout << "The supermarket is now supplying food and water for now. We can't hold supplies and keep out zombies for long so get them ASAP if possible." << std::endl;
    }
    else if (MessageRand == 2)
    {
        std::cout << "We have successfully cleared out the subway of zombies. We can't hold them out for long so please head there as soon as possible in an orderly manner." << std::endl;
    }
    else if (MessageRand == 3)
    {
        std::cout << "Someone is trapped inside the hospital. They say they have a cure." << std::endl;
    }
    else if (MessageRand == 4)
    {
        std::cout << "This is Dr. Chen. Do not trust anyone wearing a military uniform." << std::endl;
    }
    EventTimer = 120;
}

StoryManager::StoryManager() :

    // Quests

    // QUEST NAME, QUEST DESCRIPTION
    killZombieQuest("Kill 3 Zombies", "Kill 3 Zombies somewhere in the city"),

    findMissingPersonQuest("Find Timothy", "Find Timothy somewhere in the city"),

    findPharmacyQuest("Search for Temozolomide", "Search for Temozolomide in the Pharmacy section of the Supermarket"),

    // NPCS

    // NAME, DESCRIPTION, X, Y, SYMBOL, DIALOGUE, QUEST
    zombieNPC(
        "Iris",
        "A survivor who is looking for help",
        1, 1, 'i',
        &killZombieQuest,
        "There is a bunch of zombies in the city, please kill them before they attack anyone else!"
        "There are still some zombies roaming around. Help to elimate the rest of them.",
        "Thank you for killing the zombies!"
    ),

    missingpersonNPC(
        "Hank",
        "A police officer searching for a missing civilian",
        1, 1, 'h',
        &findMissingPersonQuest,
        "Someone went missing during the outbreak. His name is Timothy. Please find them and bring them back to me."
        "Please find Timothy, first.",
        "You found Timothy. Thank You so much!"
    ),

    pharmacyNPC("Dr. Chen",
        "A doctor who is looking for a cure",
        1, 1, 'd',
        &findPharmacyQuest,
        "I need to get the Temozolomide from the pharmacy section of the supermarket. Please help to retrieve it and bring it back to me",
        "Please bring me the Temozolomide.",
        "You found the Temozolomide!"
    ),

    timothyNPC(
        "Timothy",
        "A missing survivor",
        1, 1, 't',
        nullptr,
        "Thank you for finding me!"
    )
{}

void StoryManager::showQuests() const
{
    std::cout << "========================================" << std::endl
              << "          Quests          " << std::endl
              << "========================================" << std::endl;

    bool hasQuest = false;

    if (killZombieQuest.isAccepted())
    {
        hasQuest = true;
        
        std::cout << "1. " << killZombieQuest.getName() << std::endl;
        std::cout << "   " << killZombieQuest.getDescription() << std::endl;

        if (killZombieQuest.isCompleted())
        {
            std::cout << "   Status: " << GREEN << "Completed" << RESET << std::endl << std::endl;
        }
        else
        {
            std::cout << "   Progress: " << zombiesKilled << "/3" << std::endl;
            std::cout << "   Status: " << RED << "Incomplete" << RESET << std::endl << std::endl;
        }
    }

    if (findMissingPersonQuest.isAccepted())
    {
        hasQuest = true;

        std::cout << "2. " << findMissingPersonQuest.getName() << std::endl;
        std::cout << "   " << findMissingPersonQuest.getDescription() << std::endl;

        if (findMissingPersonQuest.isCompleted())
        {
            std::cout << "   Status: " << GREEN << "Completed" << RESET << std::endl << std::endl;
        }
        else if (timothyFound)
        {
            std::cout << "   Status: Return to " << missingpersonNPC.getName() << std::endl << std::endl;
        }
        else
        {
            std::cout << "   Status: Find " << timothyNPC.getName() << std::endl << std::endl;
        }
    }

    if (findPharmacyQuest.isAccepted())
    {
        hasQuest = true;

        std::cout << "3. " << findPharmacyQuest.getName() << std::endl;
        std::cout << "   " << findPharmacyQuest.getDescription() << std::endl;

        if (findPharmacyQuest.isCompleted())
        {
            std::cout << "   Status: " << GREEN << "Completed" << RESET << std::endl << std::endl;
        }
        else if (temozolomideFound)
        {
            std::cout << "   Status: Return to " << pharmacyNPC.getName() << std::endl << std::endl;
        }
        else
        {
            std::cout << "   Status: Find Temozolomide" << std::endl << std::endl;
        }
    }

    if (!hasQuest)
    {
        std::cout << "No quests claimed." << std::endl;
    }
    
}

NPC& StoryManager::getZombieNPC()
{
    return zombieNPC;
}

NPC& StoryManager::getmissingpersonNPC()
{
    return missingpersonNPC;
}

NPC& StoryManager::getpharmacyNPC()
{
    return pharmacyNPC;
}

Quest& StoryManager::getkillZombieQuest()
{
    return killZombieQuest;
}

Quest& StoryManager::getfindMissingPersonQuest()
{
    return findMissingPersonQuest;
}

Quest& StoryManager::getfindPharmacyQuest()
{
    return findPharmacyQuest;
}

int StoryManager::getCompletedQuestsCount() const {

    int count = 0;

    if (killZombieQuest.isCompleted()) {
        count++;
    }

    if (findMissingPersonQuest.isCompleted()) {
        count++;
    }

    if (findPharmacyQuest.isCompleted()) {
        count++;
    }

    return count;

}
      
bool StoryManager::allQuestsCompleted() const {
    return getCompletedQuestsCount() == 3;
}

NPC& StoryManager::getTimothyNPC()
{
    return timothyNPC;
}

void StoryManager::addZombieKill()
{
    if (killZombieQuest.isAccepted() && !killZombieQuest.isCompleted())
    {
        zombiesKilled++;

        if (zombiesKilled > 3)
        {
            zombiesKilled = 3;
        }
    }
}

int StoryManager::getZombiesKilled() const
{
    return zombiesKilled;
}

void StoryManager::findTimothy()
{
    if (findMissingPersonQuest.isAccepted())
    {
        timothyFound = true;
    }
}

bool StoryManager::isTimothyFound() const
{
    return timothyFound;
}

void StoryManager::findTemozolomide()
{
    temozolomideFound = true;
}

bool StoryManager::isTemozolomideFound() const
{
    return temozolomideFound;
}