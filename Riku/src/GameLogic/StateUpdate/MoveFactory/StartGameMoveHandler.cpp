#include "StartGameMoveHandler.h"
#include "../Move/GenerateMap.h"	
#include "../../GameState.h"
#include "../../Actions/SendPatchToAll.h"
#include "../../Actions/ResetCummulatedPatch.h"

StartGameMoveHandler::StartGameMoveHandler(GameState& state)
	: state(state) { }

std::shared_ptr<IMove> StartGameMoveHandler::handleDescription(const IMoveDescription& description)
{
	state.isInGame = true;
	int playerCount = state.hotSeatPlayers.size();
	for (const auto& inv : state.invitedPlayers)
		if (inv.second.state == InvitationState::Joined)
			playerCount += inv.second.hotseatCount;

	return std::make_shared<GenerateMap>(playerCount);
}

bool StartGameMoveHandler::canHandle(const IMoveDescription& description) const
{
	return description.getMoveType() == "start_game";
}
