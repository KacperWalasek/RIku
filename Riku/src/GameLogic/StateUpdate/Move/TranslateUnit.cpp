#include "TranslateUnit.h"
#include "../Patch/Patch.h"
#include "../../Unit/Unit.h"
#include "../../GameState.h"
#include "../../Utils/LogicUtils.h"

TranslateUnit::TranslateUnit(int fromX, int fromY, int toX, int toY)
    : fromX(fromX), fromY(fromY), toX(toX), toY(toY)
{}

std::shared_ptr<Patch> TranslateUnit::createPatch(const GameState& state, const LogicAssets& assets) const
{
    auto path = LogicUtils::getShortestPath(state, fromX, fromY, toX, toY);
    auto unit = state.map[fromX][fromY].unit;
    auto hookMove = unit->onBeingPlaced(toX, toY);
    auto hookPatch = hookMove ? *(hookMove->createPatch(state, assets)) : Patch();
    return std::make_shared<Patch>(
        TilePatch({ toX, toY }, unit) + 
        (Patch)TilePatch({ fromX,fromY },false,true) + 
        (Patch)UnitPatch(unit,-path.cost) +
        hookPatch);
}

bool TranslateUnit::isDoable(const GameState& state, const LogicAssets& assets) const
{
    //TODO: zoptymalizowac, zeby nie liczyc dwa razy patha. (Liczenie patha w MoveDescription?)
    auto path = LogicUtils::getShortestPath(state, fromX, fromY, toX, toY);
    const auto& unit = state.map[fromX][fromY].unit;
    std::cout << path.cost << ", " << state.map[fromX][fromY].unit->movementPoints << std::endl;
    return unit && !state.map[toX][toY].unit && unit->movementPoints >= path.cost && state.playerOnMove == unit->getOwner();
}

std::shared_ptr<IMove> TranslateUnit::asPointner() const
{
    return std::make_shared<TranslateUnit>(fromX,fromY,toX,toY);
}
