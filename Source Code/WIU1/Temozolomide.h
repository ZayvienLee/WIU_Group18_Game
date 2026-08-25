#pragma once
#include "Item.h"
class Temozolomide :
    public Item
{
public:
    Temozolomide();
    void consume(Player& player) override;
};
