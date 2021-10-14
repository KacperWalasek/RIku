//Kacper Walasek
#pragma once
#include "Response.h"
#include <vector>
#include "Tile.h"
class MapResponse : public Response
{
	const std::vector<std::vector<Tile>>& map;
public:
	MapResponse(std::shared_ptr<Request> request, const std::vector<std::vector<Tile>>& map);
	const std::vector<std::vector<Tile>>& getMap();
};

