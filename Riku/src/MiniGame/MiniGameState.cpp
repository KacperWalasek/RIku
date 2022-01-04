#include "MiniGameState.h"

minigame::MiniGameState::MiniGameState( int player, int enemy, bool begins)
	: player(player), enemy(enemy), playerOnMove(begins ? player : enemy)
{}
