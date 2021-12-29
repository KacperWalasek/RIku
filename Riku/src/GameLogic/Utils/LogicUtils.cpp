#include "LogicUtils.h"
#include <queue>
#include <list>

Path LogicUtils::getShortestPath(
    const GameState& state, int fromX, int fromY, int toX, int toY)
{
    CostEvaluator evaluator(state.map);
    return ShortestPathEvaluator::getShortestPath(evaluator, state.map.size(), state.map[0].size(), fromX, fromY, toX, toY);
}
