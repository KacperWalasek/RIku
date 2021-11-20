#include "TileObjectFactory.h"

std::shared_ptr<ITileObject> TileObjectFactory::createBase(logic::AssetData data)
{
	return std::shared_ptr<ITileObject>();
}

std::shared_ptr<ITileObject> TileObjectFactory::addBehavior(std::shared_ptr<ITileObject> base, logic::AssetData& behavior)
{
	return std::shared_ptr<ITileObject>();
}
