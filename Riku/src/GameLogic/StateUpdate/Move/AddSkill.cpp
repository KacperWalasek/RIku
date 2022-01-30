#include "AddSkill.h"
#include "../../GameState.h"
#include "../Patch/Patch.h"

AddSkill::AddSkill(std::string name, int mapX, int mapY)
    : name(name), mapX(mapX), mapY(mapY)
{}

std::shared_ptr<Patch> AddSkill::createPatch(const GameState& state, const LogicAssets& assets) const
{
    return std::make_shared<Patch>(UnitPatch(state.map[mapX][mapY].unit->getId(), name, 1));
}

bool AddSkill::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    return mapX >= 0 && mapY >= 0 && mapX < state.map.size() && mapY < state.map[0].size() && state.map[mapX][mapY].unit;
}

std::shared_ptr<IMove> AddSkill::asPointner() const
{
    return std::make_shared<AddSkill>(name, mapX, mapY);
}
