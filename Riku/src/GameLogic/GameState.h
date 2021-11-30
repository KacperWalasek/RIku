// Kacper Walasek
#pragma once
#include <vector>
#include "Tile/Tile.h"
#include "Player/Player.h"
#include <set>

class GameState
{
public:
	std::vector<Player> players;
	std::vector<std::vector<Tile>> map;
	std::set<std::shared_ptr<IHookable>> registredHookables;

	int playerOnMove = 0;
};

