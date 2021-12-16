#pragma once
#include "MiniPlayerPatch.h"
#include <map>
#include "MiniTilePatch.h"
#include <memory>
#include "../../Hooks/IMiniHookable.h"
#include "MiniRegisterHookablePatch.h"

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
	MiniPatch(MiniRegisterHookablePatch registerHookablePatch) {
		registerHookablePatches.insert({ registerHookablePatch.hookable, registerHookablePatch });
	}
	MiniPatch(bool isOnMove) : isOnMove(isOnMove ? 0 : 1) {}

	std::map<std::pair<int, int>, MiniTilePatch> tilePatches;
	std::map<std::shared_ptr<IMiniHookable>, MiniRegisterHookablePatch> registerHookablePatches;

	MiniPlayerPatch playerPatch;
	MiniPlayerPatch enemyPatch;

	int isOnMove = -1; // 0 - true; no_zero - false

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
		if (p2.isOnMove != -1)
			p1.isOnMove = p2.isOnMove;
		return std::move(p1);
	}
};

