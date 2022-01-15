#include "UseSkill.h"
#include "../../MiniGameState.h"
#include "../../MiniGameAssets.h"
#include "../../Hooks/MiniMoveWrapper.h"

minigame::UseSkill::UseSkill(std::string name, int mapX, int mapY)
    : name(name), mapX(mapX), mapY(mapY) {}

std::shared_ptr<minigame::MiniPatch> minigame::UseSkill::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto it = assets.skills.find(name);
    if (it == assets.skills.end())
        return nullptr;
    auto use = it->second.getFunction("onUse");
    MiniMoveWrapper wrapper = use(mapX, mapY);
    return wrapper.move->createPatch(state, assets);
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
