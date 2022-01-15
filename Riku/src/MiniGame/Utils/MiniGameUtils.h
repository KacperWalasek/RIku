#pragma once
#include "../../GameLogic/Utils/ShortestPathEvaluator.h"
#include "../MiniGameState.h"

namespace minigame
{
	class MiniCostEvaluator : public ICostEvaluator
	{
	public:
		virtual double h(vertex from, vertex to) override;
		virtual int d(vertex vert) override;
	};

	class MiniGameUtils
	{
	public:
		static Path getShortestPath(
			const MiniGameState& state, int fromX, int fromY, int toX, int toY);
	};

}