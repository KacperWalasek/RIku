//Kacper Walasek
#pragma once
#include <vector>
#include "PlayerPatch.h"
#include "TilePatch.h"
#include "RegisterHookablePatch.h"

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
	Patch(RegisterHookablePatch registerHookablePatch) {
		registerHookablePatches.insert({ registerHookablePatch.hookable, registerHookablePatch });
	}


	std::map<int,PlayerPatch> playerPatches;
	std::map<std::pair<int,int>, TilePatch> tilePatches;
	std::map<std::shared_ptr<IHookable>, RegisterHookablePatch> registerHookablePatches;

	friend Patch operator+(Patch p1, const Patch& p2)
	{
		for (auto plPatch2 : p2.playerPatches)
		{
			auto plPatch1 = p1.playerPatches.find(plPatch2.first);
			if (plPatch1 != p1.playerPatches.end())
				plPatch1->second += plPatch2.second;
			else
				p1.playerPatches.insert({ plPatch2 });
		}
		for (auto tilePatch2 : p2.tilePatches)
		{
			auto tilePatch1 = p1.tilePatches.find(tilePatch2.first);
			if (tilePatch1 != p1.tilePatches.end())
				tilePatch1->second += tilePatch2.second;
			else
				p1.tilePatches.insert({ tilePatch2 });
		}
		for (auto registerPatch2 : p2.registerHookablePatches)
		{
			auto registerPatch1 = p1.registerHookablePatches.find(registerPatch2.first);
			if (registerPatch1 != p1.registerHookablePatches.end())
				registerPatch1->second += registerPatch2.second;
			else
				p1.registerHookablePatches.insert({ registerPatch2 });
		}
		return std::move(p1);
	}
};

