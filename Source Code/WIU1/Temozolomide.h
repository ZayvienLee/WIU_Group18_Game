#pragma once
#include "QuestItem.h"
#include "Player.h"

class Temozolomide : public QuestItem
{
public:
    Temozolomide();
    void consume(Player& player) override;
};
