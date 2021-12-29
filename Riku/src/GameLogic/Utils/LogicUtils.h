#pragma once
#include "../GameState.h"
#include "Path.h"
#include "ShortestPathEvaluator.h"

class LogicUtils
{
public:
	static Path getShortestPath(
        const GameState& state, int fromX, int fromY, int toX, int toY);
};

