#pragma once
#include "IAction.h"
#include <iostream>
#include "../StateUpdate/StateUpdate.h"

class Patch;
class SendPatchToAll : public IAction
{
public:
	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory)
	{
		std::shared_ptr<Patch> patch = stateUpdate.getCummulatedPatch();
		// TODO:webModule send patch to all using web module
	}
};
