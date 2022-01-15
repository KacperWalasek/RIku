#pragma once
#include "../../GameLogic/Utils/ShortestPathEvaluator.h"
#include "../MiniGameState.h"

namespace minigame
{
	class MiniCostEvaluator : public ICostEvaluator
	{
	public:
		virtual int h(vertex from, vertex to) override;
		virtual int d(vertex vert) override;
	};

	class MiniGameUtils
	{
		static std::map<std::string, std::shared_ptr<IMiniHookable>> hookables;
	public:
		static Path getShortestPath(
			const MiniGameState& state, int fromX, int fromY, int toX, int toY, int movementPoints = 0);

		static void addHookable(std::shared_ptr<IMiniHookable> hookable);
		static void removeHookable(std::string id);
		static std::shared_ptr<IMiniHookable> getHookable(std::string id);
		static void clearHookables();
	};

}