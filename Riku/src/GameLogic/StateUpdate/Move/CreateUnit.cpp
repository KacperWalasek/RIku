#include "CreateUnit.h"

CreateUnit::CreateUnit(int player, std::string unit, LogicAssets& assets) 
    : player(player), name(name), assets(assets)
{}

std::shared_ptr<Patch> CreateUnit::createPatch(const GameState& state) const
{
    return std::make_shared<Patch>(PlayerPatch(player, std::make_shared<Unit>("unit", "unit", 2, std::map<std::string, sol::function>())));
}

bool CreateUnit::isDoable(const GameState& state) const
{
    return true;
}
