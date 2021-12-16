#pragma once
#include "Tile/MiniTile.h"
#include "../GameLogic/GameState.h"
#include "Player/MiniGamePlayer.h"

class MiniGameState
{
public:
	MiniGameState(GameState& gameState, int player, int enemy, bool begins);
	GameState& gameState;
	std::vector<std::vector<MiniTile>> map;
	MiniGamePlayer player;
	MiniGamePlayer enemy;

	bool isOnMove;
};

