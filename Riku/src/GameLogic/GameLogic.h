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
	std::shared_ptr<IMiniGame> getActiveMiniGame() const;
public:
	GameLogic(std::string assetPath);
	std::shared_ptr<Response> getInfo(std::shared_ptr<Request> request) const;
	template<typename T>
	std::shared_ptr<T> getInfo(std::shared_ptr<Request> request) const
	{
		return std::static_pointer_cast<T>(getInfo(request));
	}
	template<typename T>
	std::shared_ptr<T> getInfo(std::string requestType) const
	{
		return getInfo<T>(std::make_shared<Request>(requestType));
	}
	void makeMove(std::shared_ptr<IMoveDescription> moveDescription);
	bool isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const;
};

