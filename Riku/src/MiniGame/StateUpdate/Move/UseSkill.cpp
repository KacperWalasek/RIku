#include "UseSkill.h"
#include "../../MiniGameState.h"
#include "../../MiniGameAssets.h"
#include "../../Hooks/MiniMoveWrapper.h"
#include "../../../GameLogic/Utils/LogicUtils.h"
#include "../Patch/MiniPatch.h"

minigame::UseSkill::UseSkill(std::string name, int mapX, int mapY)
    : name(name), mapX(mapX), mapY(mapY) {}

std::shared_ptr<minigame::MiniPatch> minigame::UseSkill::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto it = assets.skills.find(name);
    if (it == assets.skills.end())
        return nullptr;
    auto use = it->second.getFunction("onUse");
    MiniMoveWrapper wrapper = use(mapX, mapY);
    try
    {
        MiniMoveWrapper wrapper = use(mapX, mapY);
        if (!wrapper.move->isDoable(state, assets))
        {
            LogicUtils::addPopup("You cannot use skill on this tile");
            return nullptr;
        }
        return std::make_shared<MiniPatch>(*wrapper.move->createPatch(state, assets) + MiniPatch(MiniPlayerPatch(name,true)));
    }
    catch (...)
    {
        LogicUtils::addPopup("Error in skill definition");
        return nullptr;
    }
}

bool minigame::UseSkill::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto it = std::find(state.player.skills.begin(), state.player.skills.end(), name);
    return it != state.player.skills.end() && state.playerOnMove == state.player.logicIndex;
}

std::shared_ptr<minigame::IMiniMove> minigame::UseSkill::asPointner() const
{
    return std::make_shared<UseSkill>(name, mapX, mapY);
}
