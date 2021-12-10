#pragma once
#include <memory>
#include "../../MiniGameState.h"

class MiniPatch;
class IMiniMove;
class IMiniPatchHandler
{
public:
	virtual std::shared_ptr<IMiniMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const = 0;
};

