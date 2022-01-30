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
    if (state.map.size() != 0)
        return std::make_shared<Patch>(state.playerOnMove);
    auto map = assets.mapGenerator.getFunction("onCreateMap")().get<std::vector<std::vector<TileDescription>>>();
    std::shared_ptr<IMove> combined = nullptr;;
    for(int i = 0; i< map.size(); i++)
        for (int j = 0; j < map[i].size(); j++)
            if(map[i][j].tileObject != "")
            {
                std::shared_ptr<IMove> build = std::make_shared<BuildTileObject>(-1, std::make_pair( i,j ),map[i][j].tileObject);
                combined = combined ? std::make_shared<CombinedMove>(combined, build) : build;
            }
    for (int i = 0; i < playerCount; i++)
    {
        // TODO: when players will be map change player index
        std::shared_ptr<IMove> create = std::make_shared<CreateUnit>(i, "stefan", 0, i);
        combined = combined ? std::make_shared<CombinedMove>(combined, create) : create;
    }
    Patch patch = Patch(map) + Patch(combined) + Patch(0);
    patch.playerCount = playerCount;
    return std::make_shared<Patch>(patch);
}

bool GenerateMap::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    return true;
}

std::shared_ptr<IMove> GenerateMap::asPointner() const
{
    return std::make_shared<GenerateMap>(playerCount);
}
