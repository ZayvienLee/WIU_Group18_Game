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
                std::cout << "Alright, I can give you this " << NPCitem << " for your " << Playeritem << ". Is it a good deal? " <<
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
                std::cout << "Yeah I would love to! I can give you this " << NPCitem << " for your " << Playeritem << ". Is it a good deal? " <<
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
        if (Reputation == 1 and SideQuest == 1)
        {
            int Temozolomide = 1; //delete this when Item.h has initialised the item
            if (Temozolomide == 1)
            {
                std::cout << "Oh you found it! Just putting it there and...voila! Here's the cure, let me know if you really want to invite me out!" << std::endl;
                int Cure = 1; //remove int when Item.h has initialised the item
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
            std::cout << "Hello there, what brings you here today?" << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" or decision == "(1)")
            {
                std::cout << "Alright, I can follow you but it's dangerous out there, you'll need to brave enough.";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "Okay, let me know when you need me.";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "Alright, I can give you this " << NPCitem << " for your " << Playeritem << ". Is it a good deal? " <<
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
                std::cout << "Some corners of this police station has a living rodent running around. Catch it and try to bring it to me.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "What the hell?";
                Reputation -= 1;
            }
        }
        if (Reputation == 0 and SideQuest == 1)
        {
            int Ammo = 0; //remove this when Ammunition.h has initialised the item
            int Rat = 1; //delete this when Item.h has initialised the item
            if (Rat == 1)
            {
                std::cout << "Woah thanks, you deserve some ammo so have some." << std::endl;
                Ammo += 5; //remove int when Ammunition.h has initialised the item
                Reputation += 1;
            }
            else if (Rat == 0)
            {
                std::cout << "Catching rodents ain't easy, keep your head up kid." << std::endl;
            }
        }
        if (Reputation == 1 and SideQuest == 0)
        {
            std::cout << "Welcome my man. How can I assist you today?" << std::endl <<
                "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                "(5) Betray them";
            std::cin >> decision;
            if (decision == "1" or decision == "(1)")
            {
                std::cout << "Of course! This land isn't easy being alone.";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "Okay, let me know when you need me.";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "Alright, I can give you this " << NPCitem << " for your" << Playeritem << ".Is it a good deal ? " <<
                    std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                if (decision == "1" or "(1)")
                {
                    std::cout << "Thanks for the trade man." << std::endl;
                    Reputation += 1;
                }
                if (decision == "2" or "(2)")
                {
                    std::cout << "Okay, let me know when you need me." << std::endl;
                }

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "Some corners of this police station has a living rodent running around. Catch it and try to bring it to me.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "Don't do it again.";
                Reputation -= 1;
            }
        }
        if (Reputation == 1 and SideQuest == 1)
        {
            int Ammo = 0; //remove this when Ammunition.h has initialised the item
            int Rat = 1; //delete this when Item.h has initialised the item
            if (Rat == 1)
            {
                std::cout << "Impressive work, here's some more ammo for your effort." << std::endl;
                Ammo += 10; //remove int when Item.h has initialised the item
            }
            else if (Rat == 0)
            {
                std::cout << "Catching rodents ain't easy, keep your head up kid." << std::endl;
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
                std::cout << "Why ask me?";
                Reputation += 1;
            }
            else if (decision == "2" or decision == "(2)")
            {
                std::cout << "...";
            }
            else if (decision == "3" or decision == "(3)")
            {
                std::cout << "Why the hell would I want to trade with you?" << std::endl;

            }
            else if (decision == "4" or decision == "(4)")
            {
                std::cout << "So you finally wanted to help after betraying me. Heh. Grab that rat and show me your worth.";
                SideQuest = 1;
            }
            else if (decision == "5" or decision == "(5)")
            {
                std::cout << "I'm not trusting you anymore.";
            }
        }
        if (Reputation == -1 and SideQuest == 1)
        {
            int Ammo = 0; //remove this when Ammunition.h has initialised the item
            int Rat = 1; //delete this when Item.h has initialised the item
            if (Rat == 1)
            {
                std::cout << "About time, here's some ammo for your effort at least." << std::endl;
                Ammo += 3; //remove int when Ammunition.h has initialised the item
                Reputation += 1;
            }
            else if (Rat == 0)
            {
                std::cout << "Stop standing around and get to work." << std::endl;
            }
        }
        if (NPC == 3)
        {
            if (Reputation == 0 and SideQuest == 0)
            {
                std::cout << "Oh hi! Do you need any assistance around here?" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Yes! I love adventures! Bring it on king, I'll show you the way!";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "Alright, let me know!";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your "<< Playeritem << ". Is it a good deal? " <<
                        std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                    if (decision == "1" or "(1)")
                    {
                        std::cout << "Alright here you go, thanks for the trade!" << std::endl;
                        Reputation += 1;
                    }
                    if (decision == "2" or "(2)")
                    {
                        std::cout << "I understand, let me know when you need it!" << std::endl;
                    }

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I need a special gem from the abandoned Subway so we can sell it once we arrive in Haven-7, good luck man!";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "What's wrong with you??";
                    Reputation -= 1;
                }
            }
            if (Reputation == 0 and SideQuest == 1)
            {
                int Gem = 1; //delete this when Item.h has initialised the item
                if (Gem == 1)
                {
                    std::cout << "You actually got the gem? Sick! Here's some food and water for your work!" << std::endl;
                    int Burger = 2; //remove int when Item.h has initialised the item
                    int WaterBottle = 2; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Gem == 0)
                {
                    std::cout << "I have never seen anyone come back after talking to me. Please make me proud!" << std::endl;
                }
            }
            if (Reputation == 1 and SideQuest == 0)
            {
                std::cout << "Love your tunes there! How can I help you?" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Woah! Really? That's so awesome! I'll definitely go and show you everywhere!";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "No worries man, keep it up!";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your" << Playeritem << ".Is it a good deal ? " <<
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
                    std::cout << "I need to have a very special Gem from the Subway, please bring it to me!";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "Bro, that's not cool.";
                    Reputation -= 1;
                }
            }
            if (Reputation == 1 and SideQuest == 1)
            {
                int Gem = 1; //delete this when Item.h has initialised the item
                if (Gem == 1)
                {
                    std::cout << "You actually got the gem? Sick! Really feeling generous so here's some nutrients for your work!" << std::endl;
                    int Burger = 3; //remove int when Item.h has initialised the item
                    int WaterBottle = 3; //remove int when Item.h has initialised the item
                }
                else if (Gem == 0)
                {
                    std::cout << "I have never seen anyone come back after talking to me. Please make me proud!" << std::endl;
                }
            }
            if (Reputation == -1 and SideQuest == 0)
            {
                std::cout << "... *visibly sobbing*" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "...";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "...";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "..." << std::endl;

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I guess desperate times comes desperate actions, i'll give you a chance once and let you find a gem in the subway. Bring it to me and i'll consider.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "...";
                }
            }
            if (Reputation == -1 and SideQuest == 1)
            {
                int Gem = 1; //delete this when Item.h has initialised the item
                if (Gem == 1)
                {
                    std::cout << "Well that's something at least, thanks so much." << std::endl;
                    int Burger = 1; //remove int when Item.h has initialised the item
                    int WaterBottle = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Gem == 0)
                {
                    std::cout << "..." << std::endl;
                }
            }
        }
        if (NPC == 4)
        {
            if (Reputation == 0 and SideQuest == 0)
            {
                std::cout << "Sup man, you up for a moment?" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Sick man, let's go.";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "Please come back when you need me!";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your" << Playeritem << ".Is it a good deal ? " <<
                        std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                    if (decision == "1" or "(1)")
                    {
                        std::cout << "Cool trade man, thanks... hehe" << std::endl;
                        Reputation += 1;
                    }
                    if (decision == "2" or "(2)")
                    {
                        std::cout << "Oh." << std::endl;
                    }

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I want you to slay all the zombies for me. I'll consider you a hero.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "Not cool bro.";
                    Reputation -= 1;
                }
            }
            if (Reputation == 0 and SideQuest == 1)
            {
                int SlainAllZombies = 1; //delete this when Map.h has initialised the item
                if (SlainAllZombies == 1)
                {
                    std::cout << "Sick man, thanks for the effort." << std::endl;
                    Reputation += 1;
                }
                else if (SlainAllZombies == 0)
                {
                    std::cout << "Get out there and show your worth." << std::endl;
                }
            }
            if (Reputation == 1 and SideQuest == 0)
            {
                std::cout << "Sup brah, time to roll out?" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Sick man, let's roll.";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "Alright mate, I'll let you.";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Alright, I can give you this " << NPCitem << " for your" << Playeritem << ".Is it a good deal ? " <<
                        std::endl << "(1) Yes" << std::endl << "(2) No" << std::endl;
                    if (decision == "1" or "(1)")
                    {
                        std::cout << "Appreciate it man...hehehehehehehe" << std::endl;
                        Reputation += 1;
                    }
                    if (decision == "2" or "(2)")
                    {
                        std::cout << "uh?" << std::endl;
                    }

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "I want you to slay all the zombies for me. It's not hard and I have seen your moves.";
                    SideQuest = 1;
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "Not cool man.";
                    Reputation -= 1;
                }
            }
            if (Reputation == 1 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Sick man." << std::endl;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "You can do it!" << std::endl;
                }
            }
            if (Reputation == -1 and SideQuest == 0)
            {
                std::cout << "What you want man?" << std::endl <<
                    "(1) Recruit them" << std::endl << "(2) Ignore them" << std::endl <<
                    "(3) Trade with them" << std::endl << "(4) Help them" << std::endl <<
                    "(5) Betray them";
                std::cin >> decision;
                if (decision == "1" or decision == "(1)")
                {
                    std::cout << "Not now brah.";
                    Reputation += 1;
                }
                else if (decision == "2" or decision == "(2)")
                {
                    std::cout << "So?";
                }
                else if (decision == "3" or decision == "(3)")
                {
                    std::cout << "Can't do it." << std::endl;

                }
                else if (decision == "4" or decision == "(4)")
                {
                    std::cout << "Kill all the zombies for me, can?";
                }
                else if (decision == "5" or decision == "(5)")
                {
                    std::cout << "What?";
                }
            }
            if (Reputation == -1 and SideQuest == 1)
            {
                int Temozolomide = 1; //delete this when Item.h has initialised the item
                if (Temozolomide == 1)
                {
                    std::cout << "Thanks brah." << std::endl;
                    int Cure = 1; //remove int when Item.h has initialised the item
                    Reputation += 1;
                }
                else if (Temozolomide == 0)
                {
                    std::cout << "Get out there and do your thing man." << std::endl;
                }
            }
        }
        if (Reputation > 1)
        {
            Reputation = 1;
        }
    }
}