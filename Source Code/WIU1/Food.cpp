#include "Food.h"
#include "Player.h"

Food::Food()
{
	foodPt = 30;
	name = "Food";
	description = "Increase satiety";
	x = -1;
	y = -1;
	symbol = 'f';
	inInventory = true;
	weight = 0;
	quantity = 0;
}

void Food::consume(Player& player)
{
	player.setHunger(player.getHunger() + foodPt);
	
	if (player.getHunger() > 100)
	{
		player.setHunger(100);
	}
}
