#pragma once
#include "../../GameLogic/Utils/ShortestPathEvaluator.h"
#include "../MiniGameState.h"

class MiniCostEvaluator : public ICostEvaluator
{
public:
	virtual int h(vertex from, vertex to) override;
	virtual int d(vertex vert) override;
};

class MiniGameUtils
{
public:
	static Path getShortestPath(
		const MiniGameState& state, int fromX, int fromY, int toX, int toY);
};

