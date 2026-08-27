#pragma once
#include "Quest.h"
#include "NPC.h"

class StoryManager
{
private:
    Quest killZombieQuest; // In the supermarket
    Quest findMissingPersonQuest; // In the Police Station
    Quest findPharmacyQuest; // In the Hospital
    Quest scavengePartsQuest; // In the Gas Station
    Quest killGreaterZombieQuest; // In the Military Base

    NPC zombieNPC; // The NPC which gives the quest to kill zombies
    NPC missingpersonNPC; // Gives the player a quest to find a missing person
    NPC pharmacyNPC; // gives quest to find Temozolomide in the pharmacy
    NPC timothyNPC; // He is required for one of the quests above
    NPC mechanicNPC; // Gives a quest to pass mechanical parts
    NPC militaryCaptainNPC; // Similar to the above NPC, but stricter with higher number of zombie kills
    NPC safeHouseCoordinatorNPC; // The person whom the player meets at the final stages of the game

    int zombiesKilled;
    bool timothyFound;
    bool temozolomideFound;
    bool hasReceivedKeyCard;
    bool hasReceivedAccessCard;

    int TimeToNextEvent;
    int MessageRand;
    int DoneSideQuests;

public:
    StoryManager();

    void showQuests() const;

    NPC& getZombieNPC();
    NPC& getmissingpersonNPC();
    NPC& getpharmacyNPC();
    NPC& getTimothyNPC();
    NPC& getMechanicNPC();
    NPC& getMilitaryCaptainNPC();
    NPC& getSafeHouseCoordinatorNPC();

    Quest& getkillZombieQuest();
    Quest& getfindMissingPersonQuest();
    Quest& getfindPharmacyQuest();
    Quest& getScavengePartsQuest();
    Quest& getKillGreaterZombieQuest();

    void addZombieKill();
    int getZombiesKilled() const;

    void findTimothy();
    bool isTimothyFound() const;

    bool allQuestsCompleted() const;
    void setReceivedKeyCard();
    bool checkHasReceivedKeyCard() const;
    void setReceivedAccessCard();
    bool checkHasReceivedAccessCard() const;

    int getCompletedQuestsCount() const;

    void storyIntro(); // gives intro to the story before game starts

    int GetTimeToNextEvent() const;
    int GetMessageRand() const;
    void SetTimeToNextEvent();
    void SetMessageRand();
    void decrementTimeToNextEvent();
    void RadioMessage(int playerHealth = 100); // This is prone to change
};