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
        TilePatch({ toX, toY }, unit->getId()) + 
        (Patch)TilePatch({ fromX,fromY },false,true) + 
        (Patch)UnitPatch(unit->getId(),-path.cost) +
        hookPatch);
}

bool TranslateUnit::isDoable(const GameState& state, const LogicAssets& assets) const
{
    //TODO: zoptymalizowac, zeby nie liczyc dwa razy patha. (Liczenie patha w MoveDescription?)
    auto path = LogicUtils::getShortestPath(state, fromX, fromY, toX, toY);
    const auto& unit = state.map[fromX][fromY].unit;
    std::cout << path.cost << ", " << state.map[fromX][fromY].unit->movementPoints << std::endl;
    return unit && unit->movementPoints >= path.cost && state.playerOnMove == unit->getOwner();
}

std::shared_ptr<IMove> TranslateUnit::asPointner() const
{
    return std::make_shared<TranslateUnit>(fromX,fromY,toX,toY);
}
