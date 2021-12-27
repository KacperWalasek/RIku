#include "Attack.h"
#include "../Patch/Patch.h"

Attack::Attack(int player, std::pair<int, int> attackedTile, std::shared_ptr<Unit> unit)
    : player(player), attackedTile(attackedTile), unit(unit)
{}

std::shared_ptr<Patch> Attack::createPatch(const GameState& state, const LogicAssets& assets) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;

    return std::make_shared<Patch>(MiniGamePatch(player, attacedUnit->getPlayer(), true) + (Patch)MiniGamePatch(attacedUnit->getPlayer(), player, false));
}

bool Attack::isDoable(const GameState& state, const LogicAssets& assets) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;
    auto distance = abs(unit->getMapX() - attackedTile.first) + abs(unit->getMapY() - attackedTile.second);

    return attacedUnit && attacedUnit->getPlayer() != player && distance == 1;
}

std::shared_ptr<IMove> Attack::asPointner() const
{
    return std::make_shared<Attack>(player, attackedTile, unit);
}
