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

void StoryManager::Dialogue()
{
    int NPC = 0; // Delete this once initialised in NPC.h and NPC.cpp
    std::string NPCitem; // Delete this once initialised in NPC.h and NPC.cpp
    int Reputation = 0; // Delete this once initialised in Player.h and Player.cpp
    std::string Playeritem; // Delete this once initialised in Player.h and Player.cpp
    std::string decision;
    if (NPC == 1)
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