#include "StoryManager.h"
#include <cstdlib>
#include <iostream>

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
    if (MessageRand = 0)
    {
        std::cout << "*Unintelligible Noises*" << std::endl;
    }
    if (MessageRand = 1)
    {
        std::cout << "The supermarket is now supplying food and water for now. We can't hold supplies and keep out zombies for long so get them ASAP if possible." << std::endl;
    }
    if (MessageRand = 2)
    {
        std::cout << "We have successfully cleared out the subway of zombies. We can't hold them out for long so please head there as soon as possible in an orderly manner." << std::endl;
    }
    if (MessageRand = 3)
    {
        std::cout << "Someone is trapped inside the hospital. They say they have a cure." << std::endl;
    }
    if (MessageRand = 4)
    {
        std::cout << "This is Dr. Chen. Do not trust anyone wearing a military uniform." << std::endl;
    }
    EventTimer = 120;
}

StoryManager::StoryManager() :

       // Quests

       // QUEST NAME, QUEST DESCRIPTION
       killZombieQuest("Kill 3 Zombies", "Kill 3 Zombies somewhere inthe city"),

       findMissingPersonQuest("Find Timothy", "Find Timothy somewhere in the city"),
    
       findPharmacyQuest("Search for Temozolomide", "Search for Temozolomide in the Pharmacy section of the Supermarket"),

       // NPCS

       // NAME, DESCRIPTION, X, Y, SYMBOL, DIALOGUE, QUEST
       zombieNPC("Alexa", "A survivor who is looking for help", 0, 0, 'AL', "There is a bunch of zombies in the city, please kill them before they attack anyone else!", &killZombieQuest),

       missingpersonNPC("George", "A police officer searching for a missing civilian", 0, 0, 'GG', "Someone went missing during the outbreak. Please find them and bring them back to me.", &findMissingPersonQuest),

       pharmacyNPC("Dr. Chen", "A doctor who is looking for a cure", 0, 0, 'DC', "I need to get the Temozolomide from the pharmacy section of the supermarket. Please help to retrieve it and bring it back to me", &findPharmacyQuest) {}

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

void StoryManager::Dialogue()
{
    int NPC = 0; // Delete this once initialised in NPC.h and NPC.cpp
    std::string NPCitem; // Delete this once initialised in NPC.h and NPC.cpp
    int Reputation = 0; // Delete this once initialised in Player.h and Player.cpp
    std::string Playeritem; // Delete this once initialised in Player.h and Player.cpp
    std::string decision;
    if (NPC == 1)
    {
        if (Reputation == 0 && SideQuest == 0)
        {
            std::cout << "Hello there. Do you need any help? " << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" || decision == "(1)")
            {
                std::cout << "Oh really? I would love to, thanks for recruiting me!";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "I see. Please come back when you need me!";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                    std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                if (decision == "1" or "(1)")
                {
                    std::cout << "Alright here you go, thanks for the trade!" << std::endl;
                    Reputation += 1;
                }
                if (decision == "2" or "(2)")
                {
                    std::cout << "I see. Please come back when you need me!" << std::endl;
                }

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "You betrayed me!";
                Reputation -= 1;
            }
        }
        if (Reputation == 0 and SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
                Reputation += 1;
            }
            else if (Temozolomide == 0)
            {
                std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
            }
        }
        if (Reputation == 1 and SideQuest == 0)
        {
            std::cout << "Heya! What can I help you with today my favourite? " << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" or decision == "(1)")
            {
                std::cout << "Of course! I'll love to help out!";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "I see. Please come back when you need me!";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                    std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                if (decision == "1" or "(1)")
                {
                    std::cout << "Here you go my fav, appreciated the trade!" << std::endl;
                    Reputation += 1;
                }
                if (decision == "2" or "(2)")
                {
                    std::cout << "I see. Please come back when you need me!" << std::endl;
                }

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "That's not nice, don't do it again.";
                Reputation -= 1;
            }
        }
        if (Reputation == 0 and SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure, let me know if you really want to invite me out!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
                Reputation += 1;
            }
            else if (Temozolomide == 0)
            {
                std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
            }
        }
        if (Reputation == -1 and SideQuest == 0)
        {
            std::cout << "What do you want?" << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" or decision == "(1)")
            {
                std::cout << "No, sorry.";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "...";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "I can't trade with you if you anger me." << std::endl;

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "Fine, i'll give you something. I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "What the hell!";
            }
        }
        if (Reputation == -1 and SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Finally something good for once! Just putting it there and...voila! Here's the cure!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
                Reputation += 1;
            }
            else if (Temozolomide == 0)
            {
                std::cout << "Why do you keep standing around me?" << std::endl;
            }
        }
    }
    if (NPC == 2)
    {
        if (Reputation == 0 and SideQuest == 0)
        {
            std::cout << "Hello there. Do you need any help? " << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" or decision == "(1)")
            {
                std::cout << "Oh really? I would love to, thanks for recruiting me!";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "I see. Please come back when you need me!";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                    std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                if (decision == "1" or "(1)")
                {
                    std::cout << "Alright here you go, thanks for the trade!" << std::endl;
                    Reputation += 1;
                }
                if (decision == "2" or "(2)")
                {
                    std::cout << "I see. Please come back when you need me!" << std::endl;
                }

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "You betrayed me!";
                Reputation -= 1;
            }
        }
        if (Reputation == 0 and SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
                Reputation += 1;
            }
            else if (Temozolomide == 0)
            {
                std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
            }
        }
        if (Reputation == 1 and SideQuest == 0)
        {
            std::cout << "Heya! What can I help you with today my favourite? " << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" or decision == "(1)")
            {
                std::cout << "Of course! I'll love to help out!";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "I see. Please come back when you need me!";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                    std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                if (decision == "1" or "(1)")
                {
                    std::cout << "Here you go my fav, appreciated the trade!" << std::endl;
                    Reputation += 1;
                }
                if (decision == "2" or "(2)")
                {
                    std::cout << "I see. Please come back when you need me!" << std::endl;
                }

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "That's not nice, don't do it again.";
                Reputation -= 1;
            }
        }
        if (Reputation == 0 and SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure, let me know if you really want to invite me out!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
                Reputation += 1;
            }
            else if (Temozolomide == 0)
            {
                std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
            }
        }
        if (Reputation == -1 and SideQuest == 0)
        {
            std::cout << "What do you want?" << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" or decision == "(1)")
            {
                std::cout << "No, sorry.";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "...";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "I can't trade with you if you anger me." << std::endl;

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "Fine, i'll give you something. I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "What the hell!";
            }
        }
        if (Reputation == -1 and SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Finally something good for once! Just putting it there and...voila! Here's the cure!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
                Reputation += 1;
            }
            else if (Temozolomide == 0)
            {
                std::cout << "Why do you keep standing around me?" << std::endl;
            }
        }
        if (NPC == 3)
        {
            if (Reputation == 0 and SideQuest == 0)
            {
                std::cout << "Hello there. Do you need any help? " << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Oh really? I would love to, thanks for recruiting me!";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "I see. Please come back when you need me!";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                        std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                    if (decision == "1" or "(1)")
                    {
                        std::cout << "Alright here you go, thanks for the trade!" << std::endl;
                        Reputation += 1;
                    }
                    if (decision == "2" or "(2)")
                    {
                        std::cout << "I see. Please come back when you need me!" << std::endl;
                    }

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "You betrayed me!";
                    Reputation -= 1;
                }
            }
            if (Reputation == 0 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure!" << std::endl;
                    int Cure = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
                }
            }
            if (Reputation == 1 and SideQuest == 0)
            {
                std::cout << "Heya! What can I help you with today my favourite? " << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Of course! I'll love to help out!";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "I see. Please come back when you need me!";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                        std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                    if (decision == "1" or "(1)")
                    {
                        std::cout << "Here you go my fav, appreciated the trade!" << std::endl;
                        Reputation += 1;
                    }
                    if (decision == "2" or "(2)")
                    {
                        std::cout << "I see. Please come back when you need me!" << std::endl;
                    }

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "That's not nice, don't do it again.";
                    Reputation -= 1;
                }
            }
            if (Reputation == 0 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure, let me know if you really want to invite me out!" << std::endl;
                    int Cure = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
                }
            }
            if (Reputation == -1 and SideQuest == 0)
            {
                std::cout << "What do you want?" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "No, sorry.";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "...";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "I can't trade with you if you anger me." << std::endl;

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "Fine, i'll give you something. I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "What the hell!";
                }
            }
            if (Reputation == -1 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Oh you found it! Finally something good for once! Just putting it there and...voila! Here's the cure!" << std::endl;
                    int Cure = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "Why do you keep standing around me?" << std::endl;
                }
            }
        }
        if (NPC == 4)
        {
            if (Reputation == 0 and SideQuest == 0)
            {
                std::cout << "Hello there. Do you need any help? " << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Oh really? I would love to, thanks for recruiting me!";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "I see. Please come back when you need me!";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                        std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                    if (decision == "1" or "(1)")
                    {
                        std::cout << "Alright here you go, thanks for the trade!" << std::endl;
                        Reputation += 1;
                    }
                    if (decision == "2" or "(2)")
                    {
                        std::cout << "I see. Please come back when you need me!" << std::endl;
                    }

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "You betrayed me!";
                    Reputation -= 1;
                }
            }
            if (Reputation == 0 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure!" << std::endl;
                    int Cure = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
                }
            }
            if (Reputation == 1 and SideQuest == 0)
            {
                std::cout << "Heya! What can I help you with today my favourite? " << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Of course! I'll love to help out!";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "I see. Please come back when you need me!";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your(item).Is it a good deal ? " <<
                        std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                    if (decision == "1" or "(1)")
                    {
                        std::cout << "Here you go my fav, appreciated the trade!" << std::endl;
                        Reputation += 1;
                    }
                    if (decision == "2" or "(2)")
                    {
                        std::cout << "I see. Please come back when you need me!" << std::endl;
                    }

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "That's not nice, don't do it again.";
                    Reputation -= 1;
                }
            }
            if (Reputation == 0 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure, let me know if you really want to invite me out!" << std::endl;
                    int Cure = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "There are a bunch of zombies out there, please be careful!" << std::endl;
                }
            }
            if (Reputation == -1 and SideQuest == 0)
            {
                std::cout << "What do you want?" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "No, sorry.";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "...";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "I can't trade with you if you anger me." << std::endl;

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "Fine, i'll give you something. I need to get the Temozolomide from the Pharmacy section of the Supermarket. If you are able to get it, I can craft a cure for you.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "What the hell!";
                }
            }
            if (Reputation == -1 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Oh you found it! Finally something good for once! Just putting it there and...voila! Here's the cure!" << std::endl;
                    int Cure = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "Why do you keep standing around me?" << std::endl;
                }
            }
        }
        if (Reputation > 1)
        {
            Reputation = 1;
        }
    }
}