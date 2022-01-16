#pragma once
#include "IAction.h"
#include <iostream>
#include "../StateUpdate/StateUpdate.h"
#include "../../Network/WebModule.h"
#include <cereal/archives/binary.hpp>

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
		std::stringstream ss;
		cereal::BinaryOutputArchive oarchive(ss);
		oarchive(patch);
		Network::WebModule::SendById(1 - gameState.hotSeatPlayers[0], Network::Patch, ss.str());
	}
};
