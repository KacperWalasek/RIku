// Kacper Walasek
#pragma once
#include "GameState.h"
#include "LogicAssets.h"
#include "StateUpdate/StateUpdate.h"
#include "FrontendCommunicator/Communicator.h"

class GameLogic
{
	GameState gameState;
	LogicAssets assets;
	StateUpdate stateUpdate;
	Communicator communicator;
public:
	GameLogic();
	std::shared_ptr<Response> getInfo(std::shared_ptr<Request> request);
};

