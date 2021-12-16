#pragma once
#include <memory>
#include "../../MiniGameState.h"
#include "../Patch/MiniPatch.h"
#include "../Move/IMiniMove.h"

class IMiniPatchHandler
{
public:
	virtual void handlePatch(MiniGameState& state, const MiniPatch& patch) const = 0;
};

