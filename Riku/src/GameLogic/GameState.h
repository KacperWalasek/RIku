// Kacper Walasek
#pragma once
#include <vector>
#include "Tile/Tile.h"
#include "Player/Player.h"

class GameState
{
public:
	std::vector<Player> players;
	std::vector<std::vector<Tile>> map;
};
