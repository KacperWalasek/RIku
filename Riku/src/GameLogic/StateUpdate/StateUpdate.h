//Kacper Walasek
#pragma once
#include "Move/IMove.h"
#include "./Patch/Patch.h"
#include "./PatchHandler/IPatchHandler.h"
#include "../LogicAssets.h"

class StateUpdate
{
	std::shared_ptr<Patch> cummulatedPatch;
	GameState& state;
	const LogicAssets& assets;
	std::vector<std::shared_ptr<IPatchHandler>> patchHandlers;
public:
	std::shared_ptr<IAction> handlePatch(std::shared_ptr<Patch> patch, bool addToCummulatedPatch = true);
	void setHandlers(std::vector<std::shared_ptr<IPatchHandler>> patchHandlers);
	StateUpdate(GameState& state, const LogicAssets& assets);
	std::shared_ptr<IAction> handleMove(const std::shared_ptr<IMove> move);

	std::shared_ptr<Patch> getCummulatedPatch() const;
	void resetCummulatedPatch();
};

