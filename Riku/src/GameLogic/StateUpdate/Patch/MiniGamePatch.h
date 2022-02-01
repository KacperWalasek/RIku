//Kacper Walasek
#pragma once
#include <map>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include "../../Unit/Unit.h"
#include "../../../MiniGame/StateUpdate/Patch/MiniPatch.h"
class MiniGamePatch
{
public:
	MiniGamePatch() : player(0), playerUnit(""), enemyUnit(""), isBegining(true), remove(false), resetCummulatedPatch(false) {}
	MiniGamePatch(int player, std::string playerUnit, std::string enemyUnit, bool isBegining)
		: player(player), playerUnit(playerUnit), enemyUnit(enemyUnit), isBegining(isBegining), remove(false), resetCummulatedPatch(false) {}
	MiniGamePatch(int player, bool resetCummulatedPatch, bool remove) 
		: player(player), resetCummulatedPatch(resetCummulatedPatch), isBegining(), remove(remove) {}
	MiniGamePatch(int player, std::shared_ptr<minigame::MiniPatch> patch)
		: player(player), miniPatch(patch), isBegining(), remove(false), resetCummulatedPatch(false){}
	int player;
	std::string playerUnit, enemyUnit;
	bool isBegining;
	bool remove;
	bool resetCummulatedPatch;
	std::shared_ptr<minigame::MiniPatch> miniPatch;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(player, playerUnit, enemyUnit, isBegining, remove, resetCummulatedPatch, miniPatch);
	}

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
			if(patch.miniPatch)
				miniPatch = patch.miniPatch;
			resetCummulatedPatch = patch.resetCummulatedPatch;
		}
		return *this;
	}
};
