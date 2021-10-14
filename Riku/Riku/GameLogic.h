// Kacper Walasek
#pragma once
#include "GameState.h"
#include "LogicResources.h"
#include "StateUpdate.h"
#include "Communicator.h"

class GameLogic
{
	GameState gameState;
	LogicResources resources;
	StateUpdate stateUpdate;
	Communicator communicator;
public:
	GameLogic();
	std::shared_ptr<Response> getInfo(std::shared_ptr<Request> request);
};

