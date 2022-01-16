#include "GenerateMap.h"
#include "../../LogicAssets.h"
#include "../../Tile/TileDescription.h"
#include "../Patch/Patch.h"
#include "../../Tile/MapGenerator.h"
#include "BuildTileObject.h"
#include "CombinedMove.h"
#include "CreateUnit.h"

GenerateMap::GenerateMap(int playerCount)
    : playerCount(playerCount)
{
}

std::shared_ptr<Patch> GenerateMap::createPatch(const GameState& state, const LogicAssets& assets) const
{
    auto map = assets.mapGenerator.getFunction("onCreateMap")().get<std::vector<std::vector<TileDescription>>>();
    Patch combined = Patch();
    for(int i = 0; i< map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
        {
            BuildTileObject build(-1, { i,j },map[i][j].tileObject);
            combined = combined + *(build.createPatch(state, assets));
        }
    for (int i = 0; i < playerCount; i++)
    {
        // TODO: when players will be map change player index
        auto create = CreateUnit(i, "stefan", 0, i);
        combined = combined + *(create.createPatch(state, assets));
    }
    combined.playerCount = playerCount;
    return std::make_shared<Patch>(Patch(map) + combined + Patch(0));
}

bool GenerateMap::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return true;
}

std::shared_ptr<IMove> GenerateMap::asPointner() const
{
    return std::make_shared<GenerateMap>(playerCount);
}
