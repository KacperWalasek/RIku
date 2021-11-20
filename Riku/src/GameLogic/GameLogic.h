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
	template<typename T>
	std::shared_ptr<T> getInfo(std::shared_ptr<Request> request)
	{
		return std::static_pointer_cast<T>(getInfo(request));
	}
	template<typename T>
	std::shared_ptr<T> getInfo(std::string requestType)
	{
		return getInfo<T>(std::make_shared<Request>(requestType));
	}
};

