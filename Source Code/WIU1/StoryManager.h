#pragma once
#include "Quest.h"
#include "NPC.h"

class StoryManager
{
private:
    Quest killZombieQuest;
    Quest findMissingPersonQuest;
    Quest findPharmacyQuest;
    
    NPC zombieNPC;
    NPC missingpersonNPC;
    NPC pharmacyNPC;


	int TimeToNextEvent = 0;
	int MessageRand = 0;
<<<<<<< Updated upstream
	int DoneSideQuests = 0;
=======

>>>>>>> Stashed changes
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

	int GetTimeToNextEvent() const;
	int GetMessageRand() const;
	void SetTimeToNextEvent();
	void SetMessageRand();
	void RadioMessage();
	void Dialogue();
};