#pragma once
#include "Tile/MiniTile.h"
#include "Player/MiniGamePlayer.h"
#include "Hooks/IMiniHookable.h"
#include <set>
class MiniGameState
{
public:
	MiniGameState(int player, int enemy, bool begins);
	std::vector<std::vector<MiniTile>> map;
	MiniGamePlayer player;
	MiniGamePlayer enemy;
	std::set<std::shared_ptr<IMiniHookable>> registredHookables;

	bool isOnMove;
};

