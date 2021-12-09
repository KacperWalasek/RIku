// Kacper Walasek
#include "LogicAssets.h"
#include "Assets/AssetUtils.h"

void LogicAssets::initialize(std::string assetPath)
{
	handler.findFiles(assetPath);

	biomes = AssetUtils::readNumericAsset<Biome>("biomes", handler);
	areas = AssetUtils::readNumericAsset<Area>("areas", handler);
	grounds = AssetUtils::readNumericAsset<Ground>("grounds", handler);
	playerResources = AssetUtils::readStringArray<Resource>("resources",handler);
	tileObjects = AssetUtils::getAllAssetsWithType("tileobject", handler);
	units = AssetUtils::getAllAssetsWithType("unit", handler);
	mapGenerator = std::move(handler.findAsset("map_generator").value().get());
	handler.assetNodes.erase("map_generator");
	// TODO - catch wrong structure and types as errors
}
