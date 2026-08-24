#pragma once
#include "Quest.h"
#include "NPC.h"

class StoryManager
{
private:
    Quest killZombieQuest;
    Quest findMissingPersonQuest;
    Quest findPharmacyQuest;
    
    NPC zombieNPC; // The NPC which gives the quest to kill zombies
    NPC missingpersonNPC; // Gives the player a quest to find a missing person
    NPC pharmacyNPC; // gives quest to find Temozolomide in the pharmacy


	int TimeToNextEvent = 0;
	int MessageRand = 0;
	int DoneSideQuests = 0;
    
protected:
	int EventTimer = 0;
	int SideQuest = 0;
    
public:
    StoryManager();

    NPC& getZombieNPC();
    NPC& getmissingpersonNPC();
    NPC& getpharmacyNPC();

    Quest& getkillZombieQuest();
    Quest& getfindMissingPersonQuest();
    Quest& getfindPharmacyQuest();

    bool allQuestsCompleted() const;

    int getCompletedQuestsCount() const;

    void showQuests() const;

    void storyIntro(); // gives intro to the story before game starts

	int GetTimeToNextEvent() const;
	int GetMessageRand() const;
	void SetTimeToNextEvent();
	void SetMessageRand();
	void RadioMessage();
	void Dialogue();
};