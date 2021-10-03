//Kacper Walasek
#pragma once
#include "GameState.h"
#include "IMove.h"

class StateUpdate
{
	GameState& state;
public:
	StateUpdate(GameState& state);
	void handleMoveRequest(const IMove& move);
};

