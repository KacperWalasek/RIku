// Kacper Walasek
#pragma once
#include "GameState.h"
#include "LogicResources.h"
#include "Communicator.h"

class GameLogic
{
	GameState gameState;
	LogicResources resources;
	Communicator communicator;
public:
	GameLogic();
	Response* getInfo(std::shared_ptr<Request> request);
};

