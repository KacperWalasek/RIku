//Kacper Walasek
#pragma once
#include "GameState.h"
#include "Patch.h"
class IPatchHandler
{
public:
	virtual void handlePatch(GameState& state, const Patch& patch) const = 0;
};

