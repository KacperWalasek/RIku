#include "TranslateMiniUnit.h"
#include "../../Utils/MiniGameUtils.h"
#include "../../Unit/MiniUnit.h"
#include "../Patch/MiniPatch.h"

minigame::TranslateMiniUnit::TranslateMiniUnit(int fromX, int fromY, int toX, int toY)
	: fromX(fromX), fromY(fromY), toX(toX), toY(toY) {}

std::shared_ptr<minigame::MiniPatch> minigame::TranslateMiniUnit::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto path = MiniGameUtils::getShortestPath(state, fromX, fromY, toX, toY);
    auto unit = state.map[fromX][fromY].unit;
    return std::make_shared<MiniPatch>(
        MiniTilePatch({ toX, toY }, unit->getId()) +
        (MiniPatch)MiniTilePatch({ fromX,fromY }, true) +
        (MiniPatch)MiniUnitPatch(unit->getId(), -path.cost) + 
        (MiniPatch)MiniUnitPatch(unit->getId(), toX, toY));
}

bool minigame::TranslateMiniUnit::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    //TODO: zoptymalizowac, zeby nie liczyc dwa razy patha. (Liczenie patha w MoveDescription?)
    auto path = MiniGameUtils::getShortestPath(state, fromX, fromY, toX, toY);
    const auto& unit = state.map[fromX][fromY].unit;
    return unit && !state.map[toX][toY].unit && unit->movementPoints >= path.cost && state.playerOnMove == unit->getOwner();
}

std::shared_ptr<minigame::IMiniMove> minigame::TranslateMiniUnit::asPointner() const
{
	return std::make_shared<TranslateMiniUnit>(fromX,fromY,toX,toY);
}
