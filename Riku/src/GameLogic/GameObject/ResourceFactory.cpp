//Kacper Walasek
#include "ResourceFactory.h"
#include "../StateUpdate/Move/ExtractResources.h"
#include "../StateUpdate/Move/CombinedMove.h"

ResourceFactory::ResourceFactory(std::shared_ptr<ITileObject> next, int resource, int quantity) : TileObjectDecorator(next), resource(resource), quantity(quantity) {}

std::shared_ptr<IMove> ResourceFactory::onTurnEnd()
{
	if (mapX < 0 || mapY < 0) // fabryka nie stoi na ¿adnym polu
		return TileObjectDecorator::onTurnEnd();
	// TODO: player index
	auto extract = std::make_shared<ExtractResources>(getOwner(), resource, quantity, mapX, mapY, resource);
	return std::make_shared<CombinedMove>(extract, TileObjectDecorator::onTurnEnd());
}

std::shared_ptr<IMove> ResourceFactory::onBeingPlaced(int mapX, int mapY)
{
	// TODO: get rid of mapX, mapY here
	this->mapX = mapX;
	this->mapY = mapY;
	return TileObjectDecorator::onBeingPlaced(mapX, mapY);
}


#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

CEREAL_REGISTER_TYPE(ResourceFactory);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ITileObject, ResourceFactory)
