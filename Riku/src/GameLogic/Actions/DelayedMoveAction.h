#pragma once
#include "IAction.h"
#include <iostream>
#include "../StateUpdate/StateUpdate.h"

class IMove;
class DelayedMoveAction : public IAction
{
	std::shared_ptr<IMove> move;
public:
	DelayedMoveAction(std::shared_ptr<IMove> move) : move(move) {};
	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory)
	{
		auto action = stateUpdate.handleMove(move);
		if(action)
			action->takeAction(gameState, assets, stateUpdate, communicator, factory);
	}
};
