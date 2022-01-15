#include "RequireResources.h"

RequireResources::RequireResources(std::shared_ptr<ITileObject> next, int resource) 
	: TileObjectDecorator(next), resource(resource)
{}

bool RequireResources::canBeBuilt(const GameState& state, int mapX, int mapY)
{
	return state.map[mapX][mapY].resource == resource;
}


#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

CEREAL_REGISTER_TYPE(RequireResources);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ITileObject, RequireResources)
