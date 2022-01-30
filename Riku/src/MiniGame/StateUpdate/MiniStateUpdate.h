#pragma once
#include "../MiniGameState.h"
#include "PatchHandler/IMiniPatchHandler.h"
#include "../MiniGameAssets.h"
#include "../../GameLogic/StateUpdate/Move/IMove.h"
#include "../../GameLogic/StateUpdate/Move/CombinedMove.h"

namespace minigame
{
	class MiniStateUpdate
	{
		MiniGameState& state;
		const MiniGameAssets& assets;
		std::vector<std::shared_ptr<IMiniPatchHandler>> patchHandlers;
		std::shared_ptr<MiniPatch> cummulatedPatch;
	public:
		std::shared_ptr<IMove> handlePatch(std::shared_ptr<MiniPatch> patch, bool addToCummulatedPatch = true);
		void setHandlers(std::vector<std::shared_ptr<IMiniPatchHandler>> patchHandlers);
		MiniStateUpdate(MiniGameState& state, const MiniGameAssets& assets);
		std::shared_ptr<IMove> handleMove(const std::shared_ptr<IMiniMove> move);

		std::shared_ptr<MiniPatch> getCummulatedPatch() const;
		void resetCummulatedPatch();
	};

}