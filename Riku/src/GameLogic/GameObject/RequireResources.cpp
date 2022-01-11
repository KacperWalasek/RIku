#include "RequireResources.h"

RequireResources::RequireResources(std::shared_ptr<ITileObject> next, int resource) 
	: TileObjectDecorator(next), resource(resource)
{}

bool RequireResources::canBeBuilt(const GameState& state, int mapX, int mapY)
{
	return state.map[mapX][mapY].resource == resource && TileObjectDecorator::canBeBuilt(state, mapX, mapY);
}
