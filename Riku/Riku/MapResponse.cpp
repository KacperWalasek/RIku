#include "MapResponse.h"

MapResponse::MapResponse(std::shared_ptr<Request> request, const std::vector<std::vector<Tile>>& map) : Response(request, true), map(map)
{}

const std::vector<std::vector<Tile>>& MapResponse::getMap()
{
	return map;
}
