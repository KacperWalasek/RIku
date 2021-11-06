// Kacper Walasek
#pragma once
#include "GameState.h"
#include "LogicAssets.h"
#include "StateUpdate/StateUpdate.h"
#include "FrontendCommunicator/Communicator.h"
#include "StateUpdate/MoveFactory/MoveFactory.h"

class GameLogic
{
	GameState gameState;
	LogicAssets assets;
	StateUpdate stateUpdate;
	Communicator communicator;
	MoveFactory factory;
public:
	GameLogic();
	std::shared_ptr<Response> getInfo(std::shared_ptr<Request> request) const;
	void makeMove(std::shared_ptr<IMoveDescription> moveDescription);
	bool isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const;
};

