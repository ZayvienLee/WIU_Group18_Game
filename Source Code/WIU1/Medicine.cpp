#include "Medicine.h"
#include "Player.h"

Medicine::Medicine()
{
	recoverHp = 30;
	name = "Medicine";
	description = "let the player to recover Hp";
	x = -1;
	y = -1;
	symbol = 'm';
	inInventory = true;
	weight = 0;
	quantity = 0;
}

void Medicine::consume(Player& player)
{
	player.setHealth(player.getHealth() + recoverHp);

	if (player.getHealth() > 100)
	{
		player.setHealth(100);
	}
}
