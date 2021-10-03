// Kacper Walasek
#pragma once
#include "GameState.h"
#include "LogicResources.h"
#include "StateUpdate.h"

class GameLogic
{
	GameState gameState;
	LogicResources resources;
	StateUpdate stateUpdate;
public:
	GameLogic();
};

