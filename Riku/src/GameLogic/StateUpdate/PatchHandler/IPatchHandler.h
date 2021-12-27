//Kacper Walasek
#pragma once
#include "../Patch/Patch.h"

class IPatchHandler
{
public:
	virtual std::shared_ptr<IMove> handlePatch(GameState& state, const Patch& patch) const = 0;
};

