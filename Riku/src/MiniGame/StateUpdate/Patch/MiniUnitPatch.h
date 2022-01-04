#pragma once
#include <memory>
#include "../../Unit/MiniUnit.h"

namespace minigame
{
	class MiniUnitPatch
	{
	public:
		MiniUnitPatch(std::shared_ptr<MiniUnit> unit, int movementPointsChange)
			: unit(unit), movementPointsChange(movementPointsChange)
		{}
		MiniUnitPatch(std::shared_ptr<MiniUnit> unit, int mapX, int mapY)
			: unit(unit), mapX(mapX), mapY(mapY)
		{}
		std::shared_ptr<MiniUnit> unit;
		int movementPointsChange = 0;
		int mapX = -1;
		int mapY = -1;

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