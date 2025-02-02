#include "TileObjectDecoratorFactory.h"
#include "ResourceFactory.h"
#include "RequireResources.h"
#include "UseResourceOnBuild.h"
#include "Unbuildable.h"
std::shared_ptr<TileObjectDecorator> TileObjectDecoratorFactory::createTileObject(std::string type, std::map<std::string, logic::AssetData> data, std::shared_ptr<ITileObject> base, const LogicAssets& assets)
{
	// TODO - zrobi� to jako� �adniej i bardziej rozszerzalnie
	if (type == "resource_factory")
	{
		const std::vector<Resource>& resources = assets.playerResources;
		std::string resourceName = data.at("resource").asString();
		int resourceIndex = std::distance(resources.begin(),
			std::find_if(resources.begin(), resources.end(), [resourceName](const Resource& r) { return r.getName() == resourceName; }));
		return std::make_shared<ResourceFactory>(base, resourceIndex, data.at("quantity").asNumber());
	}
	if (type == "require_resources")
	{
		const std::vector<Resource>& resources = assets.playerResources;
		std::string resourceName = data.at("resource").asString();
		int resourceIndex = std::distance(resources.begin(),
			std::find_if(resources.begin(), resources.end(), [resourceName](const Resource& r) { return r.getName() == resourceName; }));
		return std::make_shared<RequireResources>(base, resourceIndex);
	}
	if (type == "use_resources")
	{
		const std::vector<Resource>& resources = assets.playerResources;
		std::string resourceName = data.at("resource").asString();
		int resourceIndex = std::distance(resources.begin(),
			std::find_if(resources.begin(), resources.end(), [resourceName](const Resource& r) { return r.getName() == resourceName; }));
		return std::make_shared<UseResourceOnBuild>(base, resourceIndex, data.at("quantity").asNumber());
	}
	if (type == "unbuildable")
		return std::make_shared<Unbuildable>(base);
	return nullptr;
}
