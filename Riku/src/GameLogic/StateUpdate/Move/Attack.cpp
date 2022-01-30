#include "Attack.h"
#include "../Patch/Patch.h"
#include "EndMiniGameTurn.h"

Attack::Attack(int player, std::pair<int, int> attackedTile, std::shared_ptr<Unit> unit)
    : player(player), attackedTile(attackedTile), unit(unit)
{}

std::shared_ptr<Patch> Attack::createPatch(const GameState& state, const LogicAssets& assets) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;

    return std::make_shared<Patch>(
        MiniGamePatch(unit->getOwner(), unit->getId(), attacedUnit->getId(), true) + 
        (Patch)MiniGamePatch(attacedUnit->getOwner(), attacedUnit->getId(), unit->getId(), false) + 
        Patch(std::make_shared<EndMiniGameTurn>(player, attacedUnit->getOwner())));
}

bool Attack::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    auto attacedUnit = state.map[attackedTile.first][attackedTile.second].unit;
    auto distance = abs(unit->getMapX() - attackedTile.first) + abs(unit->getMapY() - attackedTile.second);

    return attacedUnit && attacedUnit->getOwner() != player && distance == 1;
}

std::shared_ptr<IMove> Attack::asPointner() const
{
    return std::make_shared<Attack>(player, attackedTile, unit);
}
