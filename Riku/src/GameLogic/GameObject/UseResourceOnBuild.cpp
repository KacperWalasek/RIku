#include "UseResourceOnBuild.h"

UseResourceOnBuild::UseResourceOnBuild(std::shared_ptr<ITileObject> next, int resource, int quantity)
	: TileObjectDecorator(next), resource(resource), quantity(quantity)
{}

bool UseResourceOnBuild::canBeBuilt(const GameState & state, int mapX, int mapY)
{
	//TODO: index playera
	return state.players[0].getResourceQuantity(resource)>=quantity && TileObjectDecorator::canBeBuilt(state,mapX,mapY);
}

std::shared_ptr<IMove> UseResourceOnBuild::onBeingPlaced(int mapX, int mapY)
{
	return std::make_shared<UseResources>(resource,quantity);
}


