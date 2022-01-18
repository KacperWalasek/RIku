// Kacper Walasek
#pragma once
#include <vector>
#include "Tile/Tile.h"
#include "Player/Player.h"
#include "IMiniGame.h"
#include <set>
#include <map>
#include "Utils/Invitation.h"
class GameState
{
public:
	std::string name;
	std::map<std::string, Invitation> invitedPlayers;
	std::map<std::string, std::string> recivedInvitations;
	bool isHosting = false;
	bool isInGame = false;
	std::vector<int> hotSeatPlayers = { 0 };
	int winner = -1;

	std::vector<Player> players;
	std::vector<std::vector<Tile>> map;
	std::map<std::string, std::shared_ptr<IHookable>> registredHookables;
	std::map<int,std::shared_ptr<IMiniGame>> minigames;

	int playerOnMove = 0;
};

