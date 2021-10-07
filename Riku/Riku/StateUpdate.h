//Kacper Walasek
#pragma once
#include "GameState.h"
#include "IMove.h"
#include "Patch.h"
#include "IPatchHandler.h"

class StateUpdate
{
	GameState& state;
	std::vector<std::shared_ptr<IPatchHandler>> patchHandlers;
	void handlePatch(std::shared_ptr<Patch> patch);
public:
	void setHandlers(std::vector<std::shared_ptr<IPatchHandler>> patchHandlers);
	StateUpdate(GameState& state);
	void handleMove(const IMove& move);
};

