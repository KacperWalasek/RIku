#pragma once
#include "IAction.h"
#include <iostream>

class TestAction : public IAction
{
public:
	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory)
	{
		std::cout << "TestAction" << std::endl;
	}
};
