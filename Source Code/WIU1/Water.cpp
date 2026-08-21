#include "Water.h"
#include "Player.h"

Water::Water()
{
	waterPt = 40;
	name = "Water";
	description = "Keep yourself Hydrated";
	x = -1;
	y = -1;
	symbol = 'w';
	inInventory = true;
	weight = 500;
	quantity = 5;
}

void Water::consume(Player& player)
{
	player.setThirst(player.getThirst() + waterPt);

	if (player.getThirst() > 100)
	{
		player.setThirst(100);
	}
}
