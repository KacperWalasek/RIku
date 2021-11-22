#pragma once
#include "IPatchHandler.h"

class TilePatchHandler : public IPatchHandler
{
public:
	virtual void handlePatch(GameState& state, const Patch& patch) const override;
};

