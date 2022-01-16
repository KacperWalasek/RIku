#include "StartGameMoveHandler.h"
#include "../Move/GenerateMap.h"	
#include "../../GameState.h"

StartGameMoveHandler::StartGameMoveHandler(GameState& state)
	: state(state) { }

std::shared_ptr<IMove> StartGameMoveHandler::handleDescription(const IMoveDescription& description)
{
	int playerCount = 0;
	for (const auto& inv : state.invitedPlayers)
		if (inv.second.state == InvitationState::Joined)
			playerCount++;

	return std::make_shared<GenerateMap>(playerCount);
}

bool StartGameMoveHandler::canHandle(const IMoveDescription& description) const
{
	return description.getMoveType() == "start_game";
}
