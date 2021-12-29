#include "TranslateMiniUnit.h"
#include "../../Utils/MiniGameUtils.h"
#include "../../Unit/MiniUnit.h"
#include "../Patch/MiniPatch.h"

TranslateMiniUnit::TranslateMiniUnit(int fromX, int fromY, int toX, int toY)
	: fromX(fromX), fromY(fromY), toX(toX), toY(toY) {}

std::shared_ptr<MiniPatch> TranslateMiniUnit::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto path = MiniGameUtils::getShortestPath(state, fromX, fromY, toX, toY);
    auto unit = state.map[fromX][fromY].unit;
    return std::make_shared<MiniPatch>(
        MiniTilePatch({ toX, toY }, unit) +
        (MiniPatch)MiniTilePatch({ fromX,fromY }, true) +
        (MiniPatch)MiniUnitPatch(unit, -path.cost));
}

bool TranslateMiniUnit::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    //TODO: zoptymalizowac, zeby nie liczyc dwa razy patha. (Liczenie patha w MoveDescription?)
    auto path = MiniGameUtils::getShortestPath(state, fromX, fromY, toX, toY);
    const auto& unit = state.map[fromX][fromY].unit;
    return unit && unit->movementPoints >= path.cost && state.isOnMove != unit->isEnemy();
}

std::shared_ptr<IMiniMove> TranslateMiniUnit::asPointner() const
{
	return std::make_shared<TranslateMiniUnit>(fromX,fromY,toX,toY);
}
