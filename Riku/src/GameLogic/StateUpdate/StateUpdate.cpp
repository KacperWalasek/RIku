//Kacper Walasek
#include "StateUpdate.h"
#include "PatchHandler/PlayerPatchHandler.h"
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

void StateUpdate::handleMove(const std::shared_ptr<IMove> move)
{
	if (move != nullptr && move->isDoable(state))
		handlePatch(move->createPatch(state));
}
