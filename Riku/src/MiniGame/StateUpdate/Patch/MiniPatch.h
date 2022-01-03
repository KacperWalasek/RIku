#pragma once
#include <memory>
#include <map>
#include "../../Hooks/IMiniHookable.h"
#include "MiniPlayerPatch.h"
#include "MiniTilePatch.h"
#include "MiniRegisterHookablePatch.h"
#include "MiniUnitPatch.h"

class MiniPatch
{
public:
	MiniPatch() {};
	MiniPatch(MiniPlayerPatch playerPatch, bool enemy = false) {
		if (enemy)
			enemyPatch = playerPatch;
		else
			this->playerPatch = playerPatch;
	}
	MiniPatch(MiniTilePatch tilePatch) {
		tilePatches.insert({ tilePatch.tile, tilePatch });
	}
	MiniPatch(MiniUnitPatch unitPatch) {
		unitPatches.insert({ unitPatch.unit, unitPatch});
	}
	MiniPatch(MiniRegisterHookablePatch registerHookablePatch) {
		registerHookablePatches.insert({ registerHookablePatch.hookable, registerHookablePatch });
	}
	MiniPatch(int playerOnMove) : playerOnMove(playerOnMove) {}

	std::map<std::pair<int, int>, MiniTilePatch> tilePatches;
	std::map<std::shared_ptr<IMiniHookable>, MiniRegisterHookablePatch> registerHookablePatches;
	std::map<std::shared_ptr<MiniUnit>, MiniUnitPatch> unitPatches;

	MiniPlayerPatch playerPatch;
	MiniPlayerPatch enemyPatch;

	int playerOnMove = -1; 

	friend MiniPatch operator+(MiniPatch p1, const MiniPatch& p2)
	{
		p1.playerPatch += p2.playerPatch;
		p1.enemyPatch += p2.enemyPatch;
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

