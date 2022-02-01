#pragma once
#include "IMiniPatchHandler.h"
#include "../../../GameLogic/StateUpdate/Move/EndMiniGameTurn.h"
#include "../../../GameLogic/Utils/LogicUtils.h"

namespace minigame
{
	class IsOnMoveMiniPatchHandler :
		public IMiniPatchHandler
	{
	public:
		virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
		{
			if (patch.playerOnMove != -1)
			{
				state.playerOnMove = patch.playerOnMove;
				return std::make_shared<EndMiniGameTurn>(state.player.logicIndex, state.enemy.logicIndex);
			}
			return nullptr;
		}
	};

}