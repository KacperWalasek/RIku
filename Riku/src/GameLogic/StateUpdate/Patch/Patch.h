//Kacper Walasek
#pragma once
#include <vector>
#include "PlayerPatch.h"
#include "TilePatch.h"
#include "RegisterHookablePatch.h"
#include "UnitPatch.h"

class Patch
{
public:
	Patch() {};
	Patch(PlayerPatch playerPatch) {
		playerPatches.insert({ playerPatch.player, playerPatch });
	}
	Patch(UnitPatch unitPatch) {
		unitPatches.insert({ unitPatch.unit, unitPatch });
	}
	Patch(TilePatch tilePatch) {
		tilePatches.insert({ tilePatch.tile, tilePatch });
	}
	Patch(RegisterHookablePatch registerHookablePatch) {
		registerHookablePatches.insert({ registerHookablePatch.hookable, registerHookablePatch });
	}
	Patch(int playerOnMove) : playerOnMove(playerOnMove) {}


	std::map<int,PlayerPatch> playerPatches;
	std::map<std::pair<int,int>, TilePatch> tilePatches;
	std::map<std::shared_ptr<IHookable>, RegisterHookablePatch> registerHookablePatches;
	std::map<std::shared_ptr<Unit>, UnitPatch> unitPatches;
	int playerOnMove = -1;

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
		for (auto unitPatch2 : p2.unitPatches)
		{
			auto unitPatch1 = p1.unitPatches.find(unitPatch2.first);
			if (unitPatch1 != p1.unitPatches.end())
				unitPatch1->second += unitPatch2.second;
			else
				p1.unitPatches.insert({ unitPatch2 });
		}
		if (p2.playerOnMove != -1)
			p1.playerOnMove = p2.playerOnMove;
		return std::move(p1);
	}
};

