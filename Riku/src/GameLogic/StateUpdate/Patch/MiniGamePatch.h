//Kacper Walasek
#pragma once
#include <map>
#include "../../Unit/Unit.h"

class MiniGamePatch
{
public:
	MiniGamePatch(std::shared_ptr<Unit> playerUnit, std::shared_ptr<Unit> enemyUnit, bool isBegining)
		: player(playerUnit->getOwner()), playerUnit(playerUnit), enemyUnit(enemyUnit), isBegining(isBegining), remove(false), resetCummulatedPatch(false) {}
	MiniGamePatch(int player, bool resetCummulatedPatch, bool remove) 
		: player(player), resetCummulatedPatch(resetCummulatedPatch), isBegining(), remove(remove) {}
	MiniGamePatch(int player, std::shared_ptr<minigame::MiniPatch> patch)
		: player(player), miniPatch(patch), isBegining(), remove(false), resetCummulatedPatch(false){}
	int player;
	std::shared_ptr<Unit> playerUnit, enemyUnit;
	bool isBegining;
	bool remove;
	bool resetCummulatedPatch;
	std::shared_ptr<minigame::MiniPatch> miniPatch;

	MiniGamePatch& operator+=(const MiniGamePatch& patch)
	{
		if (player != patch.player)
			return *this;
		if (remove != patch.remove)
		{
			playerUnit = patch.playerUnit;
			enemyUnit = patch.enemyUnit;
			remove = patch.remove;
			isBegining = patch.isBegining;
			miniPatch = patch.miniPatch;
			resetCummulatedPatch = patch.resetCummulatedPatch;
		}
		return *this;
	}
};
