#pragma once
#include <map>
#include <memory>
#include "../../GameObject/ITileObject.h"
class TilePatch
{
public:
	TilePatch(std::pair<int, int> tile) : tile(tile), object(nullptr) {};
	TilePatch(std::pair<int, int> tile, std::shared_ptr<ITileObject> object) : tile(tile), object(object) {};
	std::pair<int, int> tile;
	std::shared_ptr<ITileObject> object;
};

