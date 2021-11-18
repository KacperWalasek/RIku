#include "CreateUnit.h"

CreateUnit::CreateUnit(int player, std::string unit, LogicAssets& assets) 
    : player(player), name(unit), assets(assets)
{}

std::shared_ptr<Patch> CreateUnit::createPatch(const GameState& state) const
{
    auto it = assets.units.find(name);
    if (it == assets.units.end())
        return nullptr;
    logic::Asset& asset = it->second;
    int mp = asset.getByKey("movement_points").asNumber();
    auto& funcs = asset.getFunctions();
    return std::make_shared<Patch>(PlayerPatch(player, std::make_shared<Unit>(asset.getType(), name, mp, funcs)));
}

bool CreateUnit::isDoable(const GameState& state) const
{
    return true;
}
