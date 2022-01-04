#pragma once
#include "IAction.h"
#include <iostream>
#include "../StateUpdate/StateUpdate.h"
#include "../../MiniGame/StateUpdate/Patch/MiniPatch.h"

class Patch;
class SendMiniPatch : public IAction
{
	std::shared_ptr<minigame::MiniPatch> patch;
	int enemy;
public:
	// TODO: change MiniPatch to interface or something
	SendMiniPatch(int enemy, std::shared_ptr<minigame::MiniPatch> patch)
		: patch(patch), enemy(enemy) {}

	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory)
	{
		// TODO:webModule send patch to enemy using web module
	}
};
