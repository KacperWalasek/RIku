// Kacper Walasek
#pragma once
#include <vector>
#include "Tile/Tile.h"
#include "Player/Player.h"
#include "IMiniGame.h"
#include <set>
#include <map>

class GameState
{
public:
	std::vector<Player> players;
	std::vector<std::vector<Tile>> map;
	std::map<std::string, std::shared_ptr<IHookable>> registredHookables;
	std::map<int,std::shared_ptr<IMiniGame>> minigames;

	int playerOnMove = 0;
};

