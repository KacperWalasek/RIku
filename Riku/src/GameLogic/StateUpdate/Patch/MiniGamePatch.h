//Kacper Walasek
#pragma once
#include <map>
#include "../../Unit/Unit.h"

class MiniGamePatch
{
public:
	MiniGamePatch(int player, int enemy, bool isBegining) : player(player), enemy(enemy), isBegining(isBegining), remove(false) {}
	MiniGamePatch(int player) : player(player), enemy(-1), isBegining(), remove(true) {}
	int player, enemy;
	bool isBegining;
	bool remove;

	MiniGamePatch& operator+=(const MiniGamePatch& patch)
	{
		if (player != patch.player)
			return *this;
		if (remove != patch.remove)
		{
			remove = patch.remove;
			enemy = patch.enemy;
			isBegining = patch.isBegining;
		}
		return *this;
	}
};
