#include "MiniGameAssets.h"
#include "../GameLogic/Assets/AssetUtils.h"
#include "MiniGameAssetInitializer.h"

minigame::MiniGameAssets::MiniGameAssets()
{}

void minigame::MiniGameAssets::initialize()
{
	handler.findFiles("../mini_assets", std::make_shared<MiniGameAssetInitializer>());

	units = AssetUtils::getAllAssetsWithType("minigame_unit", handler);
}
