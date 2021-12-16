#pragma once
#include "IMiniPatchHandler.h"
class IsOnMoveMiniPatchHandler :
    public IMiniPatchHandler
{
public:
    virtual void handlePatch(MiniGameState& state, const MiniPatch& patch) const override
	{
		if (patch.isOnMove != -1)
			state.isOnMove = (bool)patch.isOnMove;
	}
};

