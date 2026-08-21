#include "Medicine.h"
#include "Player.h"

Medicine::Medicine()
{
	recoverHp = 30;
}

void Medicine::consume(Player& player)
{
	player.setHealth(player.getHealth() + recoverHp);

	if (player.getHealth() > 100)
	{
		player.setHealth(100);
	}
}
