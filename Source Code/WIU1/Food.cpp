#include "Food.h"
#include "Player.h"

Food::Food()
{
	foodPt = 30;
}

void Food::consume(Player& player)
{
	player.setHunger(player.getHunger() + foodPt);
	
	if (player.getHunger() > 100)
	{
		player.setHunger(100);
	}
}

///*
//bool Food::use(Entity* target)
//{
//	Player* player = dynamic_cast<Player*>(target);
//	if (player != nullptr)
//	{
//		player->setHunger(player->getHunger() + foodPt);
//		return true;
//	}
//	return false;
//}
//*/