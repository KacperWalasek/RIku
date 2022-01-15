#include "Load.h"
#include <fstream>
#include "../../Utils/LogicUtils.h"
#include "../Patch/Patch.h"
#include "../../LogicAssets.h"
#include <cereal/archives/binary.hpp>
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include <cereal/types/polymorphic.hpp>
#include "../../../MiniGame/StateUpdate/Patch/MiniPatch.h"
#include "../../../MiniGame/MiniGame.h"
Load::Load(std::string path)
    :path(path) {}

std::shared_ptr<Patch> Load::createPatch(const GameState& state, const LogicAssets& assets) const
{
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return nullptr;

    DeserializationData data(assets, minigame::MiniGame::getAssets());
    cereal::UserDataAdapter<DeserializationData, cereal::BinaryInputArchive> iarchive(data, file);

    Patch patch;
    iarchive(patch);
    patch.clearGameState = true;
    return std::make_shared<Patch>(patch);
}

bool Load::isDoable(const GameState& state, const LogicAssets& assets) const
{
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    bool ret = file.is_open();
    file.close();
    return ret;
}

std::shared_ptr<IMove> Load::asPointner() const
{
    return std::make_shared<Load>(path);
}
