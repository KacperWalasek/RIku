//Kacper Walasek
#pragma once
#include <map>
#include "../../Unit/Unit.h"

class PlayerPatch
{
public: 
	PlayerPatch(int player) :player(player) {}
	PlayerPatch(int player, int resource, int quantity) :player(player) { resourceChanges.insert({ resource,quantity }); }
	PlayerPatch(int player, std::shared_ptr<Unit> added) : player(player) { addedUnits.push_back(added);  }

	int player;
	std::map<int, int> resourceChanges;
	std::vector<std::shared_ptr<Unit>> addedUnits;
};
