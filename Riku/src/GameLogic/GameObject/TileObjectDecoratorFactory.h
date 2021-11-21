#pragma once
#include "TileObjectDecorator.h"
#include "../Assets/AssetData.h"
#include "../LogicAssets.h"

class TileObjectDecoratorFactory
{
public:
	static std::shared_ptr<TileObjectDecorator> createTileObject(std::string type, 
		std::map<std::string, logic::AssetData> data, std::shared_ptr<ITileObject> base, LogicAssets& assets);
};

