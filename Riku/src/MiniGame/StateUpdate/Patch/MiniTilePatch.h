#pragma once
#include <cereal/types/string.hpp>
#include <cereal/types/utility.hpp>
#include "../../Unit/MiniUnit.h"

namespace minigame
{
	class MiniTilePatch
	{
	public:
		MiniTilePatch() : tile(0, 0), unit(""), removeUnit(false) {}
		MiniTilePatch(std::pair<int, int> tile, std::string unit)
			: tile(tile), unit(unit), removeUnit(false) {};
		MiniTilePatch(std::pair<int, int> tile, bool removeUnit)
			: tile(tile), unit(""), removeUnit(removeUnit) {};

		std::pair<int, int> tile;
		std::string unit;
		bool removeUnit;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(tile, unit, removeUnit);
		}

		MiniTilePatch& operator+=(const MiniTilePatch& patch)
		{
			if (tile != patch.tile)
				return *this;
			unit = (patch.unit != "" || patch.removeUnit) ? patch.unit : unit;
			removeUnit = patch.removeUnit || (removeUnit && patch.unit == "");
			return *this;
		}
	};

}