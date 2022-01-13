#include "Save.h"
#include "../../Utils/LogicUtils.h"
#include "../Patch/Patch.h"
#include "../../LogicAssets.h"
#include <cereal/archives/binary.hpp>
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include <cereal/types/polymorphic.hpp>
#include "../../../MiniGame/StateUpdate/Patch/MiniPatch.h"
#include "../../../MiniGame/MiniGame.h"
Save::Save(std::string fileName)
    :fileName(fileName) {}

std::shared_ptr<Patch>Save::createPatch(const GameState& state, const LogicAssets& assets) const
{
    DeserializationData data(assets, minigame::MiniGame::getAssets());
    auto p = minigame::MiniPatch(1, true)
        + minigame::MiniPatch(minigame::MiniPlayerPatch("julka_ciocia_stefana"), false)
        + minigame::MiniPatch(minigame::MiniPlayerPatch("rzut_oszczepem", true), false)
        + minigame::MiniTilePatch({ 1,1 }, (std::string)"jakies_id")
        + minigame::MiniRegisterHookablePatch("jakies_id")
        + minigame::MiniUnitPatch("drugie_id", 69)
        + minigame::MiniPatch( minigame::MiniPlayerPatch(
            std::make_shared<minigame::MiniUnit>("julka_ciocia_stefana", 1, 100, 
                data.miniGameAssets.units.find("julka_ciocia_stefana")->second.getFunctions(), "idUnita")));
    Patch patch = LogicUtils::createPatchFromState(state);
    std::stringstream ss;
    cereal::BinaryOutputArchive oarchive(ss);
    oarchive(p);
    cereal::UserDataAdapter<DeserializationData, cereal::BinaryInputArchive> iarchive(data, ss);
    Patch patch2;
    minigame::MiniPatch p1;
    iarchive(p1);
    return std::make_shared<Patch>();
}

bool Save::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return true;
}

std::shared_ptr<IMove> Save::asPointner() const
{
    return std::make_shared<Save>(fileName);
}
