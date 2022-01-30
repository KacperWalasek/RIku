#include "TranslateMiniUnit.h"
#include "../../Utils/MiniGameUtils.h"
#include "../../Unit/MiniUnit.h"
#include "../Patch/MiniPatch.h"

minigame::TranslateMiniUnit::TranslateMiniUnit(int fromX, int fromY, int toX, int toY)
	: fromX(fromX), fromY(fromY), toX(toX), toY(toY) {}

std::shared_ptr<minigame::MiniPatch> minigame::TranslateMiniUnit::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto unit = state.map[fromX][fromY].unit;
    int mp = unit ? unit->movementPoints : 0;
    auto path = MiniGameUtils::getShortestPath(state, fromX, fromY, toX, toY, mp);
    path.path.erase(path.path.begin() + path.reachableTilesNumber, path.path.end());
    path.cost = path.path.rbegin()->cost;

    auto&& [newToX, newToY] = path.path.rbegin()->tile;
    auto hookMove = unit->onBeingPlaced(newToX, newToY);
    auto hookPatch = hookMove ? *(hookMove->createPatch(state, assets)) : MiniPatch();
   
    return std::make_shared<MiniPatch>(
        MiniTilePatch({ newToX, newToY }, unit->getId()) +
        (MiniPatch)MiniTilePatch({ fromX,fromY }, true) +
        (MiniPatch)MiniUnitPatch(unit->getId(), -path.cost) + 
        (MiniPatch)MiniUnitPatch(unit->getId(), newToX, newToY) +
        hookPatch);
}

bool minigame::TranslateMiniUnit::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    //TODO: zoptymalizowac, zeby nie liczyc dwa razy patha. (Liczenie patha w MoveDescription?)
    const auto& unit = state.map[fromX][fromY].unit;
    int mp = unit ? unit->movementPoints : 0; 
    auto path = MiniGameUtils::getShortestPath(state, fromX, fromY, toX, toY, mp);
    return unit && path.reachableTilesNumber > 1 && state.playerOnMove == unit->getOwner();
}

std::shared_ptr<minigame::IMiniMove> minigame::TranslateMiniUnit::asPointner() const
{
	return std::make_shared<TranslateMiniUnit>(fromX,fromY,toX,toY);
}
