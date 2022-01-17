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
    auto unit = state.map[fromX][fromY].unit;
    int mp = unit ? unit->movementPoints : 0;
    auto path = LogicUtils::getShortestPath(state, fromX, fromY, toX, toY, mp);
    path.path.erase(path.path.begin() + path.reachableTilesNumber, path.path.end());

    auto&& [newToX, newToY] = path.path.rbegin()->tile;
    auto hookMove = unit->onBeingPlaced(newToX, newToY);
    auto hookPatch = hookMove ? *(hookMove->createPatch(state, assets)) : Patch();
    return std::make_shared<Patch>(
        TilePatch({ newToX, newToY }, unit->getId()) +
        (Patch)TilePatch({ fromX,fromY },false,true) + 
        (Patch)UnitPatch(unit->getId(),-path.cost) +
        (Patch)UnitPatch(unit->getId(), newToX, newToY) +
        hookPatch);
}

bool TranslateUnit::isDoable(const GameState& state, const LogicAssets& assets) const
{
    //TODO: zoptymalizowac, zeby nie liczyc dwa razy patha. (Liczenie patha w MoveDescription?)
    auto unit = state.map[fromX][fromY].unit;
    int mp = unit ? unit->movementPoints : 0;
    auto path = LogicUtils::getShortestPath(state, fromX, fromY, toX, toY, mp);
    return unit && path.reachableTilesNumber > 1 && state.playerOnMove == unit->getOwner();
}

std::shared_ptr<IMove> TranslateUnit::asPointner() const
{
    return std::make_shared<TranslateUnit>(fromX,fromY,toX,toY);
}
