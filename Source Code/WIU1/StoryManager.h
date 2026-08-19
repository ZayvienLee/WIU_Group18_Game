#pragma once

class StoryManager
{
private:
	int TimeToNextEvent = 0;
	int MessageRand = 0;
protected:
	int EventTimer = 0;
	int SideQuest = 0;
public:
	int GetTimeToNextEvent() const;
	int GetMessageRand() const;
	void SetTimeToNextEvent();
	void SetMessageRand();
	void RadioMessage();
	void Dialogue();
};