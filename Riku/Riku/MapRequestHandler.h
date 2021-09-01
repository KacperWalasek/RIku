#pragma once
#include "IRequestHandler.h"
#include <vector>
#include "Tile.h"

class MapRequestHandler : public IRequestHandler
{
	const std::vector<std::vector<Tile>>& map;
public:
	MapRequestHandler(const std::vector<std::vector<Tile>>& map) :map(map) {}
	virtual Response* handleRequest(std::shared_ptr<Request> request) override;
	virtual bool canHandle(const Request& request) const override;
};

