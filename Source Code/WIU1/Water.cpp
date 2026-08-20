#include "Water.h"

Water::Water()
{
	waterPt = 40;
}

void Water::consume(Player& player)
{
	player.setThirst(player.getThirst() + waterPt);

	if (player.getThirst() > 100)
	{
		player.setThirst(100);
	}
}

///*
//bool Water::use(Entity* target)
//{
//	Player* player = dynamic_cast<Player*>(target);
//	if (player != nullptr)
//	{
//		player->setThirst(player->getThirst() + waterPt);
//		return true;
//	}
//	return false;
//}
//*/