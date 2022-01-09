#include "MiniAttack.h"
#include "../Patch/MiniPatch.h"
#include "../../MiniGameState.h"

minigame::MiniAttack::MiniAttack(std::pair<int, int> attackedTile, std::shared_ptr<MiniUnit> unit)
    : attackedTile(attackedTile), unit(unit)
{}

std::shared_ptr<minigame::MiniPatch> minigame::MiniAttack::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;

    return std::make_shared<MiniPatch>(MiniTilePatch(attackedTile,true) + MiniPatch(MiniPlayerPatch(attacedUnit->getId(), false),true));
}

bool minigame::MiniAttack::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;
    auto distance = abs(unit->getMapX() - attackedTile.first) + abs(unit->getMapY() - attackedTile.second);

    return attacedUnit && attacedUnit->getOwner() == state.enemy.logicIndex && distance == 1;
}

std::shared_ptr<minigame::IMiniMove> minigame::MiniAttack::asPointner() const
{
    return std::make_shared<MiniAttack>(attackedTile, unit);
}
