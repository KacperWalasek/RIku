#include "MiniGameAssets.h"
#include "../GameLogic/Assets/AssetUtils.h"
#include "MiniGameAssetInitializer.h"

minigame::MiniGameAssets::MiniGameAssets()
{}

void minigame::MiniGameAssets::initialize(std::string path)
{
	handler.findFiles(path, std::make_shared<MiniGameAssetInitializer>());

	units = AssetUtils::getAllAssetsWithType("minigame_unit", handler);
	skills = AssetUtils::getAllAssetsWithType("skill", handler);
}
