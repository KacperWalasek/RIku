#pragma once
#include "../GameLogic/FrontendCommunicator/Communicator.h"
#include "MiniGameState.h"
#include "MiniGameAssets.h"
#include "StateUpdate/MiniStateUpdate.h"
#include "MoveFactory/MiniMoveFactory.h"

class MiniGame
{
	inline static MiniGameAssets assets;

	Communicator communicator;
	MiniStateUpdate stateUpdate;
	MiniGameState state;
	MiniMoveFactory factory;
public:
	static MiniGameAssets& getAssets();

	MiniGame(int player, int enemy, bool begins);

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

