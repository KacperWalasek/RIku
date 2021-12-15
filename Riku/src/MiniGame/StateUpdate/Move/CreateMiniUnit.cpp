#include "CreateMiniUnit.h"

CreateMiniUnit::CreateMiniUnit(std::string name, int mapX, int mapY, int player)
    : name(name), mapX(mapX), mapY(mapY), player(player)
{
}

std::shared_ptr<MiniPatch> CreateMiniUnit::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return std::shared_ptr<MiniPatch>();
}

bool CreateMiniUnit::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return false;
}

std::shared_ptr<IMiniMove> CreateMiniUnit::asPointner() const
{
    return std::shared_ptr<IMiniMove>();
}
