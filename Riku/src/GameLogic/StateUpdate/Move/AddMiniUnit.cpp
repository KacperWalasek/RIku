#include "AddMiniUnit.h"
#include "../../GameState.h"
#include "../Patch/Patch.h"

AddMiniUnit::AddMiniUnit(std::string name, int mapX, int mapY)
    : name(name), mapX(mapX), mapY(mapY)
{}

std::shared_ptr<Patch> AddMiniUnit::createPatch(const GameState& state, const LogicAssets& assets) const
{
    return std::make_shared<Patch>(UnitPatch(state.map[mapX][mapY].unit->getId(),name,0));
}

bool AddMiniUnit::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    return mapX >= 0 && mapY >= 0 && mapX < state.map.size() && mapY < state.map[0].size() && state.map[mapX][mapY].unit;
}

std::shared_ptr<IMove> AddMiniUnit::asPointner() const
{
    return std::make_shared<AddMiniUnit>(name, mapX, mapY);
}
