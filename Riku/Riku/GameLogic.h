// Kacper Walasek
#pragma once
#include "GameState.h"
#include "LogicAssets.h"
#include "StateUpdate.h"
#include "Communicator.h"

class GameLogic
{
	GameState gameState;
	LogicAssets resources;
	StateUpdate stateUpdate;
	Communicator communicator;
public:
	GameLogic();
	std::shared_ptr<Response> getInfo(std::shared_ptr<Request> request);
};

