#pragma once
#include "ITileObject.h"
#include "../Assets/AssetData.h"

class TileObjectFactory
{
	static std::shared_ptr<ITileObject> createBase(logic::AssetData data);
	static std::shared_ptr<ITileObject> addBehavior(std::shared_ptr<ITileObject> base, logic::AssetData& behavior);
};

