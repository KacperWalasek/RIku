#include "UseResourceOnBuild.h"

UseResourceOnBuild::UseResourceOnBuild(std::shared_ptr<ITileObject> next, int resource, int quantity)
	: TileObjectDecorator(next), resource(resource), quantity(quantity)
{}

bool UseResourceOnBuild::canBeBuilt(const GameState & state, int mapX, int mapY)
{
	//TODO: index playera
	return state.players[state.playerOnMove].getResourceQuantity(resource)>=quantity && TileObjectDecorator::canBeBuilt(state,mapX,mapY);
}

std::shared_ptr<IMove> UseResourceOnBuild::onBeingPlaced([[maybe_unused]]int mapX, [[maybe_unused]]int mapY)
{
	return std::make_shared<UseResources>(resource,quantity);
}


