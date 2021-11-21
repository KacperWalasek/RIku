#include "CreateUnit.h"

CreateUnit::CreateUnit(int player, std::string unit, int mapX, int mapY, LogicAssets& assets)
    : player(player), name(unit), assets(assets), mapX(mapX), mapY(mapY)
{}

std::shared_ptr<Patch> CreateUnit::createPatch(const GameState& state) const
{
    auto it = assets.units.find(name);
    if (it == assets.units.end())
        return nullptr;
    logic::Asset& asset = it->second;
    int mp = asset.getByKey("movement_points").asNumber();
    auto& funcs = asset.getFunctions();
    auto unitPtr = std::make_shared<Unit>(asset.getType(), name, mp, funcs);
    return std::make_shared<Patch>(PlayerPatch(player, unitPtr) + (Patch)TilePatch({mapX,mapY}, unitPtr));
}

bool CreateUnit::isDoable(const GameState& state) const
{
    return true;
}

std::shared_ptr<IMove> CreateUnit::asPointner() const
{
    return std::make_shared<CreateUnit>(player, name, mapX, mapY, assets);
}
