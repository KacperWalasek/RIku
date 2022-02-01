#pragma once
#include "Tile/MiniTile.h"
#include "Player/MiniGamePlayer.h"
#include "Hooks/IMiniHookable.h"
#include <set>

namespace minigame
{
	class MiniGameState
	{
	public:
		MiniGameState(const Unit& player, const Unit& enemy, bool begins);
		std::vector<std::vector<MiniTile>> map;
		MiniGamePlayer player;
		MiniGamePlayer enemy;
		std::set<std::string> registredHookables;

		int playerOnMove;
		int winner = -1;
	};

}