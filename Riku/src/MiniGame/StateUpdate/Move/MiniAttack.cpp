#include "MiniAttack.h"
#include "../Patch/MiniPatch.h"
#include "../../MiniGameState.h"

MiniAttack::MiniAttack(std::pair<int, int> attackedTile, std::shared_ptr<MiniUnit> unit)
    : attackedTile(attackedTile), unit(unit)
{}

std::shared_ptr<MiniPatch> MiniAttack::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;

    return std::make_shared<MiniPatch>(MiniTilePatch(attackedTile,true));
}

bool MiniAttack::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;
    auto distance = abs(unit->getMapX() - attackedTile.first) + abs(unit->getMapY() - attackedTile.second);

    return attacedUnit && attacedUnit->isEnemy() && distance == 1;
}

std::shared_ptr<IMiniMove> MiniAttack::asPointner() const
{
    return std::make_shared<MiniAttack>(attackedTile, unit);
}
