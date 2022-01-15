#pragma once
#include "IAction.h"
#include <iostream>
#include "../StateUpdate/StateUpdate.h"

class ResetCummulatedPatch : public IAction
{
public:
	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory)
	{
		stateUpdate.resetCummulatedPatch();
	}
};
