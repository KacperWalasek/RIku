#include "BuildTileObject.h"
#include "../Patch/TilePatch.h"
#include "../../GameObject/SimpleTileObject.h"
#include "../../GameObject/TileObjectDecoratorFactory.h"
#include "../Patch/Patch.h"
BuildTileObject::BuildTileObject(int player, std::pair<int, int> tile, std::string tileObject, LogicAssets& assets)
    : player(player), tile(tile), tileObject(tileObject), assets(assets)
{}

std::shared_ptr<Patch> BuildTileObject::createPatch(const GameState& state) const
{
    auto assetIt = assets.tileObjects.find(tileObject);
    if (assetIt == assets.tileObjects.end())
        return nullptr;
    logic::Asset& asset = assetIt->second;
    std::shared_ptr<ITileObject> object= std::make_shared<SimpleTileObject>( tileObject, asset.getFunctions() );
    for (auto& behavior : asset.getByKey("behavior").asMap())
    {
        std::string type = behavior.first;
        auto& dataVector = behavior.second.asVector();
        for (auto& data : dataVector)
            object = TileObjectDecoratorFactory::createTileObject(type, data.asMap(), object, assets);
    }
    return std::make_shared<Patch>(TilePatch(tile,object));
}

bool BuildTileObject::isDoable(const GameState& state) const
{
    return true;
}

std::shared_ptr<IMove> BuildTileObject::asPointner() const
{
    return std::make_shared<BuildTileObject>(player,tile,tileObject,assets);
}
