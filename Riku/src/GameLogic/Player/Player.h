// Kacper Walasek
#pragma once
#include <vector>
#include "../Unit/Unit.h"
class Player
{
	std::vector<int> resources;
public:
	std::vector<std::shared_ptr<Unit>> units;
	Player(int numberOfResources);
	void acceptResources(int type, int quantity);
	bool useResources(int type, int quantity);
	int getResourceQuantity(int type) const;

	void addUnit(std::shared_ptr<Unit> unit);
};

