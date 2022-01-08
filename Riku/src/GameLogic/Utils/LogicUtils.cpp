#include "LogicUtils.h"
#include <queue>
#include <list>

unsigned int LogicUtils::currentId = 0;
int LogicUtils::logicId = 0;
std::map<std::string, std::shared_ptr<IHookable>> LogicUtils::hookables;
void LogicUtils::initialize(int logicId)
{
    LogicUtils::logicId = logicId;
}

Path LogicUtils::getShortestPath(
    const GameState& state, int fromX, int fromY, int toX, int toY)
{
    CostEvaluator evaluator(state.map);
    return ShortestPathEvaluator::getShortestPath(evaluator, state.map.size(), state.map[0].size(), fromX, fromY, toX, toY);
}

std::string LogicUtils::getUniqueId()
{
    std::string id = std::to_string(logicId) + "_" + std::to_string(currentId);
    currentId++;
    return id;
}

void LogicUtils::addHookable(std::shared_ptr<IHookable> hookable)
{
    hookables.emplace(hookable->getId(), hookable);
}

void LogicUtils::removeHookable(std::string id)
{
    hookables.erase(id);
}

std::shared_ptr<IHookable> LogicUtils::getHookable(std::string id)
{
    return hookables[id];
}

