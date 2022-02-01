#pragma once
#include "IMiniPatchHandler.h"
#include "../../../GameLogic/StateUpdate/Move/FinishMiniGame.h"
#include "../../../GameLogic/StateUpdate/Move/RemoveUnit.h"
#include "../../../GameLogic/Utils/LogicUtils.h"

namespace minigame
{
	class WinnerMiniPatchHandler :
		public IMiniPatchHandler
	{
	public:
		virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
		{
			if (patch.winner != -1)
			{
				state.winner = patch.winner;
				const MiniGamePlayer& toRemove = patch.winner == state.player.logicIndex ? state.enemy : state.player;
				auto removeUnit = std::make_shared<RemoveUnit>(toRemove.logicUnit.getMapX(), toRemove.logicUnit.getMapY());
				return std::make_shared<FinishMiniGame>(state.player.logicIndex, state.enemy.logicIndex, removeUnit);
			}
			return nullptr;
		}
	};
}
