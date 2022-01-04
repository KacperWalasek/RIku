//Kacper Walasek
#pragma once
#include <map>
#include "../../Unit/Unit.h"

class MiniGamePatch
{
public:
	MiniGamePatch(int player, int enemy, bool isBegining) 
		: player(player), enemy(enemy), isBegining(isBegining), remove(false), resetCummulatedPatch(false) {}
	MiniGamePatch(int player, bool resetCummulatedPatch, bool remove) 
		: player(player), resetCummulatedPatch(resetCummulatedPatch), enemy(-1), isBegining(), remove(remove) {}
	MiniGamePatch(int player, std::shared_ptr<minigame::MiniPatch> patch)
		: player(player), enemy(-1), miniPatch(patch), isBegining(), remove(false), resetCummulatedPatch(false){}
	int player, enemy;
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
			remove = patch.remove;
			enemy = patch.enemy;
			isBegining = patch.isBegining;
			miniPatch = patch.miniPatch;
			resetCummulatedPatch = patch.resetCummulatedPatch;
		}
		return *this;
	}
};
