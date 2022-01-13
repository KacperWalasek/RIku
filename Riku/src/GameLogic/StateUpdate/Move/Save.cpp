#include "Save.h"
#include "../../Utils/LogicUtils.h"
#include "../Patch/Patch.h"
#include "../../LogicAssets.h"
#include <cereal/archives/binary.hpp>
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include <cereal/types/polymorphic.hpp>
Save::Save(std::string fileName)
    :fileName(fileName) {}

std::shared_ptr<Patch>Save::createPatch(const GameState& state, const LogicAssets& assets) const
{
    
    Patch patch = LogicUtils::createPatchFromState(state);
    std::stringstream ss;
    cereal::BinaryOutputArchive oarchive(ss);
    oarchive(patch);
    DeserializationData data(assets);
    cereal::UserDataAdapter<DeserializationData, cereal::BinaryInputArchive> iarchive(data, ss);
    Patch patch2;
    iarchive(patch2);
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
