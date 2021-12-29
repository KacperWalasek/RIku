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
	void makeMove(std::shared_ptr<IMoveDescription> moveDescription);
	bool isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const;
};

