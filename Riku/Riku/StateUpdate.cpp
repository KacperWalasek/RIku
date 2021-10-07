//Kacper Walasek
#include "StateUpdate.h"
#include "PlayerPatchHandler.h"
void StateUpdate::handlePatch(std::shared_ptr<Patch> patch)
{
	for (auto handler : patchHandlers)
		handler->handlePatch(state, *patch);
}

void StateUpdate::setHandlers(std::vector<std::shared_ptr<IPatchHandler>> patchHandlers)
{
	this->patchHandlers = patchHandlers;
}

StateUpdate::StateUpdate(GameState& state) : state(state) {}

void StateUpdate::handleMove(const IMove& move)
{
	if (move.isDoable(state))
		handlePatch(move.apply(state));
}
