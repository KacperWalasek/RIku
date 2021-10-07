#pragma once
#include <map>

class PlayerPatch
{
public: 
	PlayerPatch(int player) :player(player) {}
	PlayerPatch(int player, int resource, int quantity) :player(player) { resourceChanges.insert({ resource,quantity }); }
	int player;
	std::map<int, int> resourceChanges;
};

