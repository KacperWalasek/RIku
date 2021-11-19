#pragma once
#include <map>
#include <memory>
#include "../../GameObject/ITileObject.h"
class TilePatch
{
public:
	TilePatch(std::pair<int, int> tile, std::shared_ptr<ITileObject> object = nullptr) : tile(tile), object(object) {};
	std::pair<int, int> tile;
	std::shared_ptr<ITileObject> object;
};

