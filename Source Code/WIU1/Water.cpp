#include "Water.h"
#include "Player.h"

Water::Water()
{
	waterPt = 40;
	name = "Water";
	description = "Decrease thirsty";
	x = -1;
	y = -1;
	symbol = 'w';
	inInventory = true;
	weight = 0;
	quantity = 0;
}

void Water::consume(Player& player)
{
	player.setThirst(player.getThirst() + waterPt);

	if (player.getThirst() > 100)
	{
		player.setThirst(100);
	}
}
