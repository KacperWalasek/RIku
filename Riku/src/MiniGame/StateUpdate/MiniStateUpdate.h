#pragma once
#include "../MiniGameState.h"
#include "PatchHandler/IMiniPatchHandler.h"
#include "../MiniGameAssets.h"

class MiniStateUpdate
{
	MiniGameState& state;
	const MiniGameAssets& assets;
	std::vector<std::shared_ptr<IMiniPatchHandler>> patchHandlers;
	void handlePatch(std::shared_ptr<MiniPatch> patch);
public:
	void setHandlers(std::vector<std::shared_ptr<IMiniPatchHandler>> patchHandlers);
	MiniStateUpdate(MiniGameState& state, const MiniGameAssets& assets);
	void handleMove(const std::shared_ptr<IMiniMove> move);
};

