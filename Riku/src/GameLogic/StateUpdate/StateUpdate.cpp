//Kacper Walasek
#include "StateUpdate.h"
#include "PatchHandler/PlayerPatchHandler.h"
#include "../Actions/CombinedAction.h"

std::shared_ptr<IAction> StateUpdate::handlePatch(std::shared_ptr<Patch> patch)
{
	if (patch)
		cummulatedPatch = cummulatedPatch ? std::make_shared<Patch>(*cummulatedPatch + *patch) : patch;

	std::shared_ptr<IAction> action;
	if (!patch)
		return nullptr;

	for (auto handler : patchHandlers)
	{
		auto retAction = handler->handlePatch(state, *patch);
		if (retAction)
			action = action ? std::make_shared<CombinedAction>(action, retAction) : retAction;
	}
	return action;
}

void StateUpdate::setHandlers(std::vector<std::shared_ptr<IPatchHandler>> patchHandlers)
{
	this->patchHandlers = patchHandlers;
}

StateUpdate::StateUpdate(GameState& state, const LogicAssets& assets) : state(state), assets(assets) {}

std::shared_ptr<IAction> StateUpdate::handleMove(const std::shared_ptr<IMove> move)
{
	if (move && move->isDoable(state, assets))
		return handlePatch(move->createPatch(state, assets));
}

std::shared_ptr<Patch> StateUpdate::getCummulatedPatch() const
{
	return cummulatedPatch;
}

void StateUpdate::resetCummulatedPatch()
{
	cummulatedPatch = std::make_shared<Patch>();
}
