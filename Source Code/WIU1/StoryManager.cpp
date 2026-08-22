#include "StoryManager.h"
#include <cstdlib>
#include <iostream>
#include "NPC.h"
#include "Quest.h"
#include <string>

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
    std::cout << "\033[1mHaven-7 is on the other side of the city." << std::endl;
    
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
       zombieNPC("Iris", "A survivor who is looking for help", 1, 1, 'i', "There is a bunch of zombies in the city, please kill them before they attack anyone else!", &killZombieQuest),

       missingpersonNPC("Hank", "A police officer searching for a missing civilian", 1, 1, 'h', "Someone went missing during the outbreak. Please find them and bring them back to me.", &findMissingPersonQuest),

       pharmacyNPC("Dr. Chen", "A doctor who is looking for a cure", 1, 1, 'd', "I need to get the Temozolomide from the pharmacy section of the supermarket. Please help to retrieve it and bring it back to me", &findPharmacyQuest) {}

void StoryManager::Dialogue()
{
    int NPC = 0; // Delete this once initialised in NPC.h and NPC.cpp
    std::string decision;

    if (NPC == 1)
    {
        if (SideQuest == 0)
        {
            std::cout << "Hello there, I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
            SideQuest = 1;
        }
        if (SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
                SideQuest = 0;
            }
            else if (Temozolomide == 0)
            {
                std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
            }
        }
    }
    if (NPC == 2)
    {
        if (SideQuest == 0)
        {
            std::cout << "Hello there, some corners of this police station has a living rodent running around. Catch it and try to bring it to me.";
            SideQuest = 1;
        }
        if (SideQuest == 1)
        {
            int Ammo = 0; //remove this when Ammunition.h has initialised the item
            int Rat = 1; //delete this when Item.h has initialised the item
            if (Rat == 1)
            {
                std::cout << "Woah thanks, you deserve some ammo so have some." << std::endl;
                Ammo += 5; //remove int when Ammunition.h has initialised the item
                SideQuest = 0;
            }
            else if (Rat == 0)
            {
                std::cout << "Catching rodents ain't easy, keep your head up kid." << std::endl;
            }
        }
    }
    if (NPC == 3)
    {
        if (SideQuest == 0)
        {
            std::cout << "Oh hi! I need a special gem from the abandoned Subway so we can sell it once we arrive in Haven-7, good luck man!";
            SideQuest = 1;
        }
        if (SideQuest == 1)
        {
            int Gem = 1; //delete this when Item.h has initialised the item
            if (Gem == 1)
            {
                std::cout << "You actually got the gem? Sick! Here's some food and water for your work!" << std::endl;
                int Burger = 2; //remove int when Item.h has initialised the item
                int WaterBottle = 2; //remove int when Item.h has initialised the item
                SideQuest = 0;
            }
            else if (Gem == 0)
            {
                std::cout << "I have never seen anyone come back after talking to me. Please make me proud!" << std::endl;
            }
        }
    }
    if (NPC == 4)
    {
        if (SideQuest == 0)
        {
            std::cout << "I want you to slay all the zombies for me. I'll consider you a hero.";
            SideQuest = 1;
        }
        if (SideQuest == 1)
        {
            int SlainAllZombies = 1; //delete this when Map.h has initialised the item
            if (SlainAllZombies == 1)
            {
                std::cout << "Sick man, thanks for the effort." << std::endl;
                SideQuest = 0;
            }
            else if (SlainAllZombies == 0)
            {
                std::cout << "Get out there and show your worth." << std::endl;
            }
        }

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