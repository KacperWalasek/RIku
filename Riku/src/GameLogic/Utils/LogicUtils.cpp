#include "LogicUtils.h"
#include <queue>
#include <list>
#include "../StateUpdate/Patch/Patch.h"

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

void LogicUtils::clearHookables()
{
    hookables.clear();
}

Patch LogicUtils::createPatchFromState(const GameState& state)
{
    Patch patch;
    for (int i = 0; i < state.players.size(); i++)
    {
        const auto& player = state.players[i];
        for (int j = 0; j < player.getResourceQuantities().size(); j++)
            patch = patch + PlayerPatch(i, j, player.getResourceQuantity(j));
        for (auto unit : player.units)
            patch = patch + PlayerPatch(i, unit);
    }
    for (const auto& hookable : state.registredHookables)
        patch = patch + RegisterHookablePatch(hookable.first);
    for (int i = 0; i < state.map.size(); i++)
        for (int j = 0; j < state.map[i].size(); j++)
        {
            if (state.map[i][j].unit)
                patch = patch + TilePatch({ i,j }, state.map[i][j].unit->getId());
            if (state.map[i][j].object)
                patch = patch + TilePatch({ i,j }, state.map[i][j].object);
        }
    patch = patch + Patch(state.map);
    patch = patch + Patch(state.playerOnMove);
    patch.playerCount = state.players.size();
    return patch;
}

