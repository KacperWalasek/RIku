//Kacper Walasek
#include "StateUpdate.h"
#include "PatchHandler/PlayerPatchHandler.h"
void StateUpdate::handlePatch(std::shared_ptr<Patch> patch)
{
	if (!patch)
		return;
	// During patch handling new moves may be created by hooks
	for (auto handler : patchHandlers)
		handleMove(handler->handlePatch(state, *patch));
}

void StateUpdate::setHandlers(std::vector<std::shared_ptr<IPatchHandler>> patchHandlers)
{
	this->patchHandlers = patchHandlers;
}

StateUpdate::StateUpdate(GameState& state, const LogicAssets& assets) : state(state), assets(assets) {}

void StateUpdate::handleMove(const std::shared_ptr<IMove> move)
{
	if (move && move->isDoable(state, assets))
		handlePatch(move->createPatch(state, assets));
}
