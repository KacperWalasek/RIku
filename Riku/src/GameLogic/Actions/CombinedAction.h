#pragma once
#include "IAction.h"
#include <memory>
class CombinedAction : public IAction
{
	std::shared_ptr<IAction> action1, action2;
public:
	CombinedAction(std::shared_ptr<IAction> action1, std::shared_ptr<IAction> action2)
		: action1(action1), action2(action2) {}
	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory)
	{
		if (action1)
			action1->takeAction(gameState, assets, stateUpdate, communicator, factory);
		if (action2)
			action2->takeAction(gameState, assets, stateUpdate, communicator, factory);
	}
};
