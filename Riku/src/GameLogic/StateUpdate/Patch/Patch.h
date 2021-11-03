//Kacper Walasek
#pragma once
#include <vector>
#include "PlayerPatch.h"
class Patch
{
public:
	Patch() {};
	Patch(PlayerPatch playerPatch) {
		playerPatches.insert({ playerPatch.player, playerPatch });
	}
	std::map<int,PlayerPatch> playerPatches;
};

