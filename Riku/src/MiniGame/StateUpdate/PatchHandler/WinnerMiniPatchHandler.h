#pragma once
#include "IMiniPatchHandler.h"
#include "../../../GameLogic/StateUpdate/Move/FinishMiniGame.h"

class WinnerMiniPatchHandler :
	public IMiniPatchHandler
{
public:
	virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
	{
		if (patch.winner != -1)
			return std::make_shared<FinishMiniGame>(state.player.logicIndex, state.enemy.logicIndex, patch.winner);
		return nullptr;
	}
};

