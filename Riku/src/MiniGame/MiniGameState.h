#pragma once
#include "Tile/MiniTile.h"
#include "../GameLogic/GameState.h"

class MiniGameState
{
public:
	MiniGameState(GameState& gameState, int player, int enemy, bool begins);
	GameState& gameState;
	std::vector<std::vector<MiniTile>> map;
	int player;
	int enemy;

	bool isOnMove;
};

