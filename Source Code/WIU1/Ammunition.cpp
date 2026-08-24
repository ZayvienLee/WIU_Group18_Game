#include "Ammunition.h"
#include "Item.h"
#include "Player.h"

Ammunition::Ammunition()
{
	name = "Ammunition";
	description = "Bullet for firearms";
	x = -1; y = -1;
	symbol = 'a';
	inInventory = true;
	weight = 50;
	quantity = 5;
}

void Ammunition::consume(Player& player)
{
	player.setAmmoCount(player.getAmmoCount() + quantity);
}