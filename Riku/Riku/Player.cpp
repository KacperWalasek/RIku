// Kacper Walasek
#include "Player.h"

Player::Player(int numberOfResources)
{
	resources = std::vector<int>(numberOfResources, 0);
}

void Player::acceptResource(int type, int quantity)
{
	if (type < 0 || type >= resources.size())
		return;
	resources[type] += quantity;
}

bool Player::useResources(int type, int quantity)
{
	if (type < 0 || type >= resources.size() || resources[type] < quantity)
		return false;
	resources[type] -= quantity;
	return true;
}

int Player::getResourceQuantity(int type) const
{
	if (type < 0 || type >= resources.size())
		return -1;
	return resources[type];
}
