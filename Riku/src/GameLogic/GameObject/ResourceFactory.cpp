//Kacper Walasek
#include "ResourceFactory.h"
#include "../StateUpdate/Move/ExtractResources.h"

ResourceFactory::ResourceFactory(std::shared_ptr<ITileObject> next, int resource, int quantity) : TileObjectDecorator(next), resource(resource), quantity(quantity) {}

std::shared_ptr<IMove> ResourceFactory::onTurnEnd()
{
	if (mapX < 0 || mapY < 0) // fabryka nie stoi na ¿adnym polu
		return TileObjectDecorator::onTurnEnd();
	// TODO + TileObjectDecorator::onTurnEnd()
	return std::make_shared<ExtractResources>(0,resource,quantity,mapX,mapY,resource);
}

std::shared_ptr<IMove> ResourceFactory::onBeingPlaced(int mapX, int mapY)
{
	this->mapX = mapX;
	this->mapY = mapY;
	return TileObjectDecorator::onBeingPlaced(mapX, mapY);
}


