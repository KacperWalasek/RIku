// Kacper Walasek
#pragma once
#include <vector>
#include "Tile/Tile.h"
#include "Player/Player.h"
#include <set>
#include <map>
#include "../MiniGame/MiniGame.h"

class GameState
{
public:
	std::vector<Player> players;
	std::vector<std::vector<Tile>> map;
	std::set<std::shared_ptr<IHookable>> registredHookables;
	//TODO: make an interface for MiniGame to make it more extencible
	std::map<int,MiniGame> minigames;

	int playerOnMove = 0;
};

