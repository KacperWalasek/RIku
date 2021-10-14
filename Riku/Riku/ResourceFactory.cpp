//Kacper Walasek
#include "ResourceFactory.h"
#include "ChangePlayerResources.h"

ResourceFactory::ResourceFactory(std::shared_ptr<ITileObject> next, int resource, int quantity) : TileObjectDecorator(next), resource(resource), quantity(quantity) {}

std::shared_ptr<IMove> ResourceFactory::onTurnEnd()
{
	return std::make_shared<ChangePlayerResources>(0,resource,quantity);
}


