#include "MiniGameUtils.h"
#include <cmath>

int minigame::MiniCostEvaluator::h(vertex from, vertex to)
{
    return (int)sqrt(pow((to.x - from.x), 2) + pow((to.y - from.y), 2));
}

int minigame::MiniCostEvaluator::d(vertex vert)
{
    return 1;
}

Path minigame::MiniGameUtils::getShortestPath(const MiniGameState& state, int fromX, int fromY, int toX, int toY)
{
    MiniCostEvaluator evaluator;
    return ShortestPathEvaluator::getShortestPath(evaluator, state.map.size(), state.map[0].size(), fromX, fromY, toX, toY);
}
