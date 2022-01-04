#pragma once
#include "../../Unit/MiniUnit.h"

namespace minigame
{
	class MiniTilePatch
	{
	public:
		MiniTilePatch(std::pair<int, int> tile, std::shared_ptr<MiniUnit> unit)
			: tile(tile), unit(unit), removeUnit(false) {};
		MiniTilePatch(std::pair<int, int> tile, bool removeUnit)
			: tile(tile), unit(nullptr), removeUnit(removeUnit) {};

		std::pair<int, int> tile;
		std::shared_ptr<MiniUnit> unit;
		bool removeUnit;

		MiniTilePatch& operator+=(const MiniTilePatch& patch)
		{
			if (tile != patch.tile)
				return *this;
			unit = (patch.unit || patch.removeUnit) ? patch.unit : unit;
			removeUnit = patch.removeUnit || (removeUnit && !patch.unit);
			return *this;
		}
	};

}