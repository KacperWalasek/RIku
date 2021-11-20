// Kacper Walasek
#include "Player.h"
#include <memory>

Player::Player(int numberOfResources)
{
	resources = std::vector<int>(numberOfResources, 0);
}

void Player::acceptResources(int type, int quantity)
{
	if (type < 0 || type >= resources.size() || quantity <= 0)
		return;
	resources[type] += quantity;
}

bool Player::useResources(int type, int quantity)
{
	if (type < 0 || type >= resources.size() || quantity <= 0 || resources[type] < quantity)
		return false;
	resources[type] -= quantity;
	return true;
}

int Player::getResourceQuantity(int type) const
{
	if (type < 0 || type >= resources.size() )
		return -1;
	return resources[type];
}

const std::vector<int>& Player::getResourceQuantities() const
{
	return resources;
}

void Player::addUnit(std::shared_ptr<Unit> unit)
{
	units.push_back(unit);
}
