#pragma once
#include "IMiniPatchHandler.h"
class RegisterHookableMiniPatchHandler :
    public IMiniPatchHandler
{
    virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
    {
		for (auto p : patch.registerHookablePatches)
		{
			if (p.second.add)
				state.registredHookables.insert(p.first);
			else
				state.registredHookables.erase(p.first);
		}

		return nullptr;
    }
};

