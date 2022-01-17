#include "RemoveUnit.h"
#include "../../GameState.h"
#include "../Patch/Patch.h"

RemoveUnit::RemoveUnit(int mapX, int mapY)
    : mapX(mapX), mapY(mapY)
{}

std::shared_ptr<Patch> RemoveUnit::createPatch(const GameState& state, const LogicAssets& assets) const
{
    std::shared_ptr<Unit> unit = state.map[mapX][mapY].unit;
    return std::make_shared<Patch>(TilePatch({mapX,mapY}, false, true) 
        + (Patch)PlayerPatch(unit->getOwner(),unit->getId()) 
        + (Patch)RegisterHookablePatch(unit->getId(),false));
}

bool RemoveUnit::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return mapX >= 0 && mapY >= 0 && mapX < state.map.size() && mapY < state.map[0].size() && state.map[mapX][mapY].unit;
}

std::shared_ptr<IMove> RemoveUnit::asPointner() const
{
    return std::make_shared<RemoveUnit>(mapX, mapY);
}
