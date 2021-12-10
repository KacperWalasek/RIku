#include "MiniGameState.h"

MiniGameState::MiniGameState(GameState& gameState, int player, int enemy, bool begins)
	: gameState(gameState), player(player), enemy(enemy), isOnMove(begins)
{}
