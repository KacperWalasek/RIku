#pragma once
#include <map>
#include <memory>
#include "../../GameObject/ITileObject.h"

class TilePatch
{
public:
	TilePatch(std::pair<int, int> tile, std::shared_ptr<ITileObject> object = nullptr) : tile(tile), object(object), unit(nullptr) {};
	TilePatch(std::pair<int, int> tile, std::shared_ptr<Unit> unit) : tile(tile), object(nullptr), unit(unit) {};
	std::pair<int, int> tile;
	std::shared_ptr<ITileObject> object;
	std::shared_ptr<Unit> unit;

	TilePatch& operator+=(const TilePatch& patch)
	{
		if (tile != patch.tile)
			return *this;
		object = patch.object;
		unit = patch.unit;
		return *this;
	}
};

