//Kacper Walasek
#pragma once
#include <vector>
#include "PlayerPatch.h"
#include "TilePatch.h"
class Patch
{
public:
	Patch() {};
	Patch(PlayerPatch playerPatch) {
		playerPatches.insert({ playerPatch.player, playerPatch });
	}
	Patch(TilePatch tilePatch) {
		tilePatches.insert({ tilePatch.tile, tilePatch });
	}
	std::map<int,PlayerPatch> playerPatches;
	std::map<std::pair<int,int>, TilePatch> tilePatches;
};

