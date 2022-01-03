#pragma once
#include <memory>
#include "../../MiniGameState.h"
#include "../Patch/MiniPatch.h"
#include "../Move/IMiniMove.h"
#include "../../../GameLogic/StateUpdate/Move/IMove.h"

class IMiniPatchHandler
{
public:
	virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const = 0;
};

