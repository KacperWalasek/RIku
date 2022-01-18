// Kacper Walasek
#include "LogicAssets.h"
#include "Assets/AssetUtils.h"
#include "Assets/LogicAssetInitializer.h"
#include "../MiniGame/MiniGame.h"

void LogicAssets::initialize(std::string assetPath, std::string miniGameAssetPath)
{
	handler.findFiles(assetPath, std::make_shared<LogicAssetInitializer>());
	minigame::MiniGame::getAssets().initialize(miniGameAssetPath);

	biomes = AssetUtils::readNumericAsset<Biome>("biomes", handler);
	areas = AssetUtils::readNumericAsset<Area>("areas", handler);
	grounds = AssetUtils::readNumericAsset<Ground>("grounds", handler);
	playerResources = AssetUtils::readStringArray<Resource>("resources",handler);
	tileObjects = AssetUtils::getAllAssetsWithType("tileobject", handler);
	units = AssetUtils::getAllAssetsWithType("unit", handler);
	mapGenerator = std::move(handler.findAsset("map_generator").value().get());
	winCondition = std::move(handler.findAsset("win_condition").value().get());
	handler.assetNodes.erase("win_condition");
	handler.assetNodes.erase("map_generator");
	// TODO - catch wrong structure and types as errors
}
