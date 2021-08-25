// Kacper Walasek
#pragma once
#include <vector>
class Player
{
	std::vector<int> resources;
public:
	Player(int numberOfResources);
	void acceptResource(int type, int quantity);
	bool useResources(int type, int quantity);
	int getResourceQuantity(int type) const;
};

