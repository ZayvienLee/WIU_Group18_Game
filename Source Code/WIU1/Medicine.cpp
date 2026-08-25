#include "Medicine.h"
#include "Player.h"
#include "GameObject.h"

Medicine::Medicine()
{
	recoverHp = 30;
	name = "Medicine";
	description = "let the player to recover Hp";
	x = -1;
	y = -1;
	symbol = 'm';
	inInventory = true;
	weight = 500;
	quantity = 1;
	colourCode = Colour::CYAN;
}

void Medicine::consume(Player& player)
{
	player.setHealth(player.getHealth() + recoverHp);

	if (player.getHealth() > 100)
	{
		player.setHealth(100);
	}
}
