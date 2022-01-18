#pragma once
#include "IAction.h"
#include <iostream>
#include "../StateUpdate/StateUpdate.h"
#include "../WinConditions/WinConditionFactory.h"
class CheckWinConditionAction : public IAction
{
public:
	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory)
	{
		WinConditionFactory winConditionfactory;
		auto winCondition = winConditionfactory.createWincondition(assets.winCondition);
		int player = winCondition->isSatisfied(gameState, assets);
		if (player != -1)
		{
			auto action = stateUpdate.handlePatch(std::make_shared<Patch>(true));
			if (action)
				action->takeAction(gameState, assets, stateUpdate, communicator, factory);
		}
	}
};
