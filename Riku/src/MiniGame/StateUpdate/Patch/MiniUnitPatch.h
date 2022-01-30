#pragma once
#include <cereal/types/string.hpp>
#include "../../Unit/MiniUnit.h"

namespace minigame
{
	class MiniUnitPatch
	{
	public:
		MiniUnitPatch() : unit("") {}
		MiniUnitPatch(std::string unit, int movementPointsChange)
			: unit(unit), movementPointsChange(movementPointsChange)
		{}
		MiniUnitPatch(std::string unit, int mapX, int mapY)
			: unit(unit), mapX(mapX), mapY(mapY)
		{}
		std::string unit;
		int movementPointsChange = 0;
		int mapX = -1;
		int mapY = -1;

		template<class Archive>
		void serialize(Archive& archive)
		{
			archive(unit, movementPointsChange, mapX, mapY);
		}

		MiniUnitPatch& operator+=(const MiniUnitPatch& patch)
		{
			if (unit != patch.unit)
				return *this;
			movementPointsChange = movementPointsChange + patch.movementPointsChange;
			mapX = patch.mapX == -1 ? mapX : patch.mapX;
			mapY = patch.mapY == -1 ? mapY : patch.mapY;
			return *this;
		}
	};

}