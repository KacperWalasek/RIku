#include "Load.h"
Load::Load(Patch patch)
    :patch(patch) {}

std::shared_ptr<Patch> Load::createPatch(const GameState& state, const LogicAssets& assets) const
{
    return std::make_shared<Patch>(patch);
}

bool Load::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    return true;
}

std::shared_ptr<IMove> Load::asPointner() const
{
    return std::make_shared<Load>(patch);
}
