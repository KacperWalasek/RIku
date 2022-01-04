#include "MiniStateUpdate.h"
#include "Move/IMiniMove.h"

std::shared_ptr<IMove> minigame::MiniStateUpdate::handlePatch(std::shared_ptr<MiniPatch> patch)
{
	// TODO Zrobic +=
	cummulatedPatch = cummulatedPatch? std::make_shared<MiniPatch>(*cummulatedPatch + (MiniPatch)(*patch)) : patch;
	std::shared_ptr<IMove> combinedMove;
	for (auto handler : patchHandlers)
	{
		std::shared_ptr<IMove> retMove = handler->handlePatch(state, *patch);
		if (retMove)
			combinedMove = std::make_shared<CombinedMove>(combinedMove, retMove);
	}
	return combinedMove;
}

void minigame::MiniStateUpdate::setHandlers(std::vector<std::shared_ptr<IMiniPatchHandler>> patchHandlers)
{
	this->patchHandlers = patchHandlers;
}

minigame::MiniStateUpdate::MiniStateUpdate(MiniGameState& state, const MiniGameAssets& assets)
	: state(state), assets(assets)
{}

std::shared_ptr<IMove> minigame::MiniStateUpdate::handleMove(const std::shared_ptr<IMiniMove> move)
{
	std::shared_ptr<IMove> combinedMove;
	if (move && move->isDoable(state, assets))
	{
		std::shared_ptr<IMove> retMove = handlePatch(move->createPatch(state, assets));
		if (retMove)
			combinedMove = std::make_shared<CombinedMove>(combinedMove, retMove);
	}
	return combinedMove;
}

std::shared_ptr<minigame::MiniPatch> minigame::MiniStateUpdate::getCummulatedPatch() const
{
	return cummulatedPatch;
}

void minigame::MiniStateUpdate::resetCummulatedPatch()
{
	cummulatedPatch = {};
}
