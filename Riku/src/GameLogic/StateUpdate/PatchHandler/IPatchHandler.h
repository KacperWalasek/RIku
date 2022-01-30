//Kacper Walasek
#pragma once
#include "../Patch/Patch.h"
#include "../../Actions/IAction.h"

class IPatchHandler
{
public:
	virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const = 0;
};

