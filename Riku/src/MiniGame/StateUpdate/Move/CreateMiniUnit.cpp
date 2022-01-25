#include "CreateMiniUnit.h"
#include "../../MiniGameAssets.h"
#include "../../MiniGameState.h"
#include "../../Unit/MiniUnit.h"
#include "../Patch/MiniPatch.h"

minigame::CreateMiniUnit::CreateMiniUnit(std::string name, int mapX, int mapY, bool enemy)
    : name(name), mapX(mapX), mapY(mapY), enemy(enemy)
{
}

std::shared_ptr<minigame::MiniPatch> minigame::CreateMiniUnit::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto it = assets.units.find(name);
    if (it == assets.units.end())
        return nullptr;
    const logic::Asset& asset = it->second;
    int mp = asset.getByKey("movement_points").asNumber();
    auto& funcs = asset.getFunctions();
    auto unitPtr = std::make_shared<MiniUnit>(name, enemy ? state.enemy.logicIndex : state.player.logicIndex, mp, funcs);
    return std::make_shared<MiniPatch>(
        MiniPatch(MiniPlayerPatch(unitPtr), enemy ) +
        (MiniPatch)MiniTilePatch({ mapX,mapY }, unitPtr->getId()) +
        (MiniPatch)MiniRegisterHookablePatch(unitPtr->getId()) +
        (MiniPatch)MiniUnitPatch(unitPtr->getId(), mapX, mapY));
}

bool minigame::CreateMiniUnit::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return assets.units.find(name) != assets.units.end() && !state.map[mapX][mapY].unit;
}

std::shared_ptr<minigame::IMiniMove> minigame::CreateMiniUnit::asPointner() const
{
    return std::make_shared<CreateMiniUnit>(name, mapX, mapY, enemy);
}
