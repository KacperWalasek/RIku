#include "Save.h"
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
Save::Save(std::string path)
    :path(path) {}

std::shared_ptr<Patch> Save::createPatch(const GameState& state, const LogicAssets& assets) const
{
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open())
        return nullptr;
    Patch patch = LogicUtils::createPatchFromState(state);
    cereal::BinaryOutputArchive oarchive(file);
    oarchive(patch);
    file.close();
    return nullptr;
}

bool Save::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return true;
}

std::shared_ptr<IMove> Save::asPointner() const
{
    return std::make_shared<Save>(path);
}
