#include "BuildTileObject.h"
#include "../Patch/TilePatch.h"
#include "../../GameObject/SimpleTileObject.h"
#include "../../GameObject/TileObjectDecoratorFactory.h"
#include "../Patch/Patch.h"
std::shared_ptr<ITileObject> BuildTileObject::createObject(const LogicAssets& assets) const
{
    auto assetIt = assets.tileObjects.find(tileObject);
    if (assetIt == assets.tileObjects.end())
        return nullptr;
    const logic::Asset& asset = assetIt->second;
    GUIDescription gui(asset.getFunctions());
    if (asset.hasData("gui"))
        gui = GUIDescription(asset.getByKey("gui").asMap(), asset.getFunctions());
    std::shared_ptr<ITileObject> object = std::make_shared<SimpleTileObject>(tileObject, player, asset.getFunctions(), gui);
	if (asset.hasData("behavior"))
	for (auto& behavior : asset.getByKey("behavior").asMap())
    {
        std::string type = behavior.first;
        auto& dataVector = behavior.second.asVector();
        for (auto& data : dataVector)
            object = TileObjectDecoratorFactory::createTileObject(type, data.asMap(), object, assets);
    }
    return object;
}
BuildTileObject::BuildTileObject(int player, std::pair<int, int> tile, std::string tileObject)
    : player(player), tile(tile), tileObject(tileObject)
{}

std::shared_ptr<Patch> BuildTileObject::createPatch(const GameState& state, const LogicAssets& assets) const
{
    std::shared_ptr<ITileObject> object = createObject(assets);
    auto placedHookMove = object->onBeingPlaced(tile.first, tile.second);
    auto creeatedHookMove = object->onBeingCreated(tile.first, tile.second);
    auto placedHookPatch = placedHookMove ? *(placedHookMove->createPatch(state, assets)) : Patch();
    auto creeatedHookPatch = creeatedHookMove ? *(creeatedHookMove->createPatch(state, assets)) : Patch();
    return std::make_shared<Patch>(TilePatch(tile,object) + (Patch)RegisterHookablePatch(object->getId()) + placedHookPatch + creeatedHookPatch);
}

bool BuildTileObject::isDoable(const GameState& state, const LogicAssets& assets) const
{
    std::shared_ptr<ITileObject> object = createObject(assets);
    auto currentObject = state.map[tile.first][tile.second].object;
    return (!currentObject || currentObject->getOwner()==-1) && assets.tileObjects.find(tileObject) != assets.tileObjects.end() && object->canBeBuilt(state,tile.first,tile.second);
}

std::shared_ptr<IMove> BuildTileObject::asPointner() const
{
    return std::make_shared<BuildTileObject>(player,tile,tileObject);
}
