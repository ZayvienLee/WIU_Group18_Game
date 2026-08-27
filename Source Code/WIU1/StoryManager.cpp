#include <cstdlib>
#include <iostream>
#include <string>
#include "StoryManager.h"
#include "NPC.h"
#include "Quest.h"

constexpr auto RESET = "\033[37m";
constexpr auto RED = "\033[31m";    /* Red */
constexpr auto GREEN = "\033[32m";  /* Green */
constexpr auto YELLOW = "\033[33m"; /* Yellow */

StoryManager::StoryManager() :

    // Quests

    // QUEST NAME, QUEST DESCRIPTION
    killZombieQuest("Kill 10 Zombies", "Kill 10 Zombies roaming around in the city"),

    findMissingPersonQuest("Find Timothy somewhere in the city", "Timothy was last seen in the School Grounds."),

    findPharmacyQuest("Search for Temozolomide", "Search for Temozolomide in the Pharmacy section of the Supermarket"),

    scavengePartsQuest("Scavenge Toolbox Parts", "Marco needs mechanical parts from somewhere in the city to keep the garage defensible."),

    killGreaterZombieQuest("Prove Your Mettle", "Reyes wants to see you've cleared at least 20 zombies before he'll trust you with military gear."),


    // NPCS

    // NAME, DESCRIPTION, X, Y, SYMBOL, DIALOGUE, QUEST
    zombieNPC(
        "Iris",
        "A survivor who is looking for help",
        6, 7, 'N',
        &killZombieQuest,
        "There is a bunch of zombies in the city, please kill them before they attack anyone else!",
        "There are still some zombies roaming around. Help to elimate the rest of them.",
        "Thank you for killing the zombies!"
    ),

    missingpersonNPC(
        "Hank",
        "A police officer searching for a missing civilian",
        3, 4, 'N',
        &findMissingPersonQuest,
        "Someone went missing during the outbreak. His name is Timothy. Please find them and bring them back to me.",
        "Please find Timothy, first.",
        "You found Timothy. Thank You so much!"
    ),

    pharmacyNPC("Dr. Chen",
        "A doctor who is looking for a cure",
        9, 10, 'N',
        &findPharmacyQuest,
        "I need to get the Temozolomide from the pharmacy section of the supermarket. Please help to retrieve it and bring it back to me",
        "Please bring me the Temozolomide.",
        "You found the Temozolomide!"
    ),

    timothyNPC(
        "Timothy",
        "A missing survivor",
        2, 3, 'N',
        nullptr,
        "Thank you for finding me!"
    ),

    mechanicNPC(
        "Marco", "A mechanic holed up in the Gas Station garage",
        4, 4, 'N',
        &scavengePartsQuest,
        "This place would be a lot safer with the right tools. If you find any toolbox parts out there, bring them here.",
        "Still need those toolbox parts, if you find any.",
        "Perfect, exactly what I needed. Here - take this, should help you carry more."
    ),

    militaryCaptainNPC(
        "Captain Reyes", "A soldier stationed at the Military Base",
        4, 4, 'N',
        &killGreaterZombieQuest,
        "You want gear from an armory, you earn it. Prove you can handle yourself out there first.",
        "Come back once you've thinned out more of them.",
        "Not bad, survivor. Here - this ought to keep you standing a bit longer."
    ),

    safeHouseCoordinatorNPC(
        "Marissa", "The Safe House coordinator, managing clearance for Haven-7",
        4, 4, 'N',
        nullptr,
        "You've made it this far. Command still needs proof you've handled things out there before I clear you for Haven-7."
    )
{
    SetTimeToNextEvent(); // This randomises the time before the next event.

    zombiesKilled = 0;
    timothyFound = false;
    temozolomideFound = false;
    hasAlreadyRecievedCard = false;
    TimeToNextEvent = 0;
    MessageRand = 0;
    DoneSideQuests = 0;
}

void StoryManager::storyIntro() {

    std::cout << "Three weeks ago, a mysterious virus spread across the city." << std::endl;
    std::cout << "At first, infected people became extremely aggressive. Within hours, hospitals were overwhelmed. The government declared an emergency and ordered everyone to remain indoors." << std::endl;
    std::cout << "Then the power went out." << std::endl;
    std::cout << "The military abandoned the city." << std::endl;
    std::cout << "The internet disappeared" << std::endl;
    std::cout << "And the dead started walking" << std::endl;
    std::cout << "You play as Alex, a survivor trapped inside an apartment building with only a small amount of food and water." << std::endl;
    std::cout << "One night, your radio suddenly turns on" << std::endl;
    std::cout << "\033[1m[RADIO] This is Haven-7. We have survivors. We have medicine. We are leaving the city in 48 hours." << std::endl;
    std::cout << "\033[0mThen the transmission cuts out" << std::endl;
    std::cout << "You have two days to reach Haven-7" << std::endl;
    std::cout << "But there is one problem." << std::endl;
    std::cout << "\033[1mHaven-7 is on the other side of the city.\033[0m" << std::endl;
    std::cout << "\033[1mFurthermore, the demilitarised zone between you and the Haven is blocked off by clearance levels.\033[0m" << std::endl;
    std::cout << "\033[1mAnd even if you have clearance, the zone is swarming with zombies ready to corner and consume those who dare to trespass.\033[0m" << std::endl;
    std::cout << "To survive, you have to utilise your resources wisely, fight through zombie hoards, help out other survivors, and prove everyone that you are capable and worthy to be a survivor." << std::endl;
    std::cout << "Good Luck!" << std::endl;
}

int StoryManager::GetTimeToNextEvent() const
{
    return TimeToNextEvent;
}

void StoryManager::SetTimeToNextEvent()
{
    TimeToNextEvent = (rand() % 31) + 30;
}

void StoryManager::SetMessageRand()
{
    MessageRand = rand() % 5;
}

int StoryManager::GetMessageRand() const
{
    return MessageRand;
}

void StoryManager::decrementTimeToNextEvent()
{
    if (TimeToNextEvent > 0) TimeToNextEvent--;
}

void StoryManager::RadioMessage(int playerHealth)
{
    if (playerHealth <= 20)
    {
        std::cout << "[RADIO] *heavy static* \"...you sound like you're in rough shape out there. Find medicine, fast.\"" << std::endl;
        return;
    }
    if (allQuestsCompleted() && !checkHasAlreadyRecievedCard())
    {
        std::cout << "[RADIO] \"This is Haven-7. All objectives clear on our end - head to the Safe House for your clearance.\"" << std::endl;
        return;
    }
    if (killZombieQuest.isAccepted() && !killZombieQuest.isCompleted())
    {
        std::cout << "[RADIO] \"Command here. Zombie activity is still high near downtown. Stay sharp out there.\"" << std::endl;
        return;
    }
    if (findMissingPersonQuest.isAccepted() && !timothyFound)
    {
        std::cout << "[RADIO] \"If anyone's near the school grounds - a survivor may still be trapped inside.\"" << std::endl;
        return;
    }
    if (findPharmacyQuest.isAccepted() && !findPharmacyQuest.isCompleted())
    {
        std::cout << "[RADIO] \"This is Dr. Chen. My supplies won't last. If you find that medicine, please hurry.\"" << std::endl;
        return;
    }

    // Fallback: original flavor lines, unchanged
    if (MessageRand == 0) std::cout << "[RADIO] *Unintelligible Noises*" << std::endl;
    else if (MessageRand == 1) std::cout << "[RADIO] \"The supermarket is now supplying food and water...\"" << std::endl;
    else if (MessageRand == 2) std::cout << "[RADIO] \"We have successfully cleared out the subway of zombies...\"" << std::endl;
    else if (MessageRand == 3) std::cout << "[RADIO] \"Someone is trapped inside the hospital. They say they have a cure.\"" << std::endl;
    else if (MessageRand == 4) std::cout << "[RADIO] \"This is Dr. Chen. Do not trust anyone wearing a military uniform.\"" << std::endl;
}

void StoryManager::showQuests() const
{
    auto printQuest = [](const Quest& q)
        {
            std::cout << " - " << q.getName() << ": ";

            if (q.isCompleted()) std::cout << GREEN << "Completed";
            else if (q.isAccepted()) std::cout << YELLOW << "In Progress";
            else std::cout << RED << "Not Accepted";

            std::cout << RESET << std::endl;
        };

    std::cout 
        << "========================================" << std::endl
        << "                 QUESTS                 " << std::endl
        << "========================================" << std::endl;

    printQuest(killZombieQuest);
    printQuest(findMissingPersonQuest);
    printQuest(findPharmacyQuest);
    printQuest(scavengePartsQuest);
    printQuest(killGreaterZombieQuest);
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

Quest& StoryManager::getScavengePartsQuest()
{
    return scavengePartsQuest;
}

Quest& StoryManager::getKillGreaterZombieQuest()
{
    return killGreaterZombieQuest;
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

    if (scavengePartsQuest.isCompleted()) {
        count++;
    }

    if (killGreaterZombieQuest.isCompleted()) {
        count++;
    }

    return count;

}
      
bool StoryManager::allQuestsCompleted() const {
    return getCompletedQuestsCount() >= 5;
}

void StoryManager::setRecievedCard()
{
    hasAlreadyRecievedCard = true;
}

bool StoryManager::checkHasAlreadyRecievedCard() const
{
    return hasAlreadyRecievedCard;
}

NPC& StoryManager::getTimothyNPC()
{
    return timothyNPC;
}

NPC& StoryManager::getMechanicNPC()
{
    return mechanicNPC;
}

NPC& StoryManager::getMilitaryCaptainNPC()
{
    return militaryCaptainNPC;
}

NPC& StoryManager::getSafeHouseCoordinatorNPC()
{
    return safeHouseCoordinatorNPC;
}

void StoryManager::addZombieKill()
{
    zombiesKilled++;
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