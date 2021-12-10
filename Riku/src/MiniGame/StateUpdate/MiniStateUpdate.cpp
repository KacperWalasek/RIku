#include "MiniStateUpdate.h"
#include "Move/IMiniMove.h"

void MiniStateUpdate::handlePatch(std::shared_ptr<MiniPatch> patch)
{
	for (auto handler : patchHandlers)
		handleMove(handler->handlePatch(state, *patch));
}

void MiniStateUpdate::setHandlers(std::vector<std::shared_ptr<IMiniPatchHandler>> patchHandlers)
{
	this->patchHandlers = patchHandlers;
}

MiniStateUpdate::MiniStateUpdate(MiniGameState& state, const MiniGameAssets& assets)
	: state(state), assets(assets)
{}

void MiniStateUpdate::handleMove(const std::shared_ptr<IMiniMove> move)
{
	if (move && move->isDoable(state, assets))
		handlePatch(move->createPatch(state, assets));
}
