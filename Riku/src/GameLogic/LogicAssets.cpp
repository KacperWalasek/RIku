// Kacper Walasek
#include "LogicAssets.h"
#include "Assets/AssetUtils.h"

void LogicAssets::initialize()
{
	logic::AssetHandler handler;
	handler.findFiles("../assets");

	biomes = AssetUtils::readNumericAsset<Biome>("biomes", handler);
	areas = AssetUtils::readNumericAsset<Area>("areas", handler);
	grounds = AssetUtils::readNumericAsset<Ground>("grounds", handler);
	playerResources = AssetUtils::readStringArray<Resource>("resources",handler);
	tileObjects = AssetUtils::getAllAssetsWithType("tileobject", handler);
	
	// TODO - catch wrong structure and types as errors
}
