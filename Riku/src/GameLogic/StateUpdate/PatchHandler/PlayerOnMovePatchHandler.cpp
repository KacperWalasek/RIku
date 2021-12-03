#include "PlayerOnMovePatchHandler.h"

std::shared_ptr<IMove> PlayerOnMovePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
	if (patch.playerOnMove >= 0 && patch.playerOnMove < state.players.size())
		state.playerOnMove = patch.playerOnMove;
	return nullptr;
}
