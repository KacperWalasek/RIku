#include "TileObjectDecoratorFactory.h"
#include "ResourceFactory.h"

std::shared_ptr<TileObjectDecorator> TileObjectDecoratorFactory::createTileObject(std::string type, std::map<std::string, logic::AssetData> data, std::shared_ptr<ITileObject> base, LogicAssets& assets)
{
	// TODO - zrobiæ to jakoœ ³adniej i bardziej rozszerzalnie
	if (type == "resource_factory")
	{
		std::vector<Resource>& resources = assets.playerResources;
		std::string resourceName = data.at("resource").asString();
		int resourceIndex = std::distance(resources.begin(),
			std::find_if(resources.begin(), resources.end(), [resourceName](const Resource& r) { return r.getName() == resourceName; }));
		return std::make_shared<ResourceFactory>(base, resourceIndex, data.at("quantity").asNumber());
	}
	return nullptr;
}
