#include "MiniGameState.h"

minigame::MiniGameState::MiniGameState(const Unit& player, const Unit& enemy, bool begins)
	: player(player), enemy(enemy), playerOnMove(begins ? player.getOwner() : enemy.getOwner())
{}
