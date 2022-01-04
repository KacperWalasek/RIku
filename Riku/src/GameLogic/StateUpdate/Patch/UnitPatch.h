#pragma once
#include <memory>

class Unit;
class UnitPatch
{
public:
	UnitPatch(std::shared_ptr<Unit> unit, int movementPointsChange)
		 : unit(unit), movementPointsChange(movementPointsChange)
	{}
	UnitPatch(std::shared_ptr<Unit> unit, int mapX, int mapY)
		: unit(unit), mapX(mapX), mapY(mapY)
	{}
	std::shared_ptr<Unit> unit;
	int movementPointsChange = 0;
	int mapX = -1;
	int mapY = -1;

	UnitPatch& operator+=(const UnitPatch& patch)
	{
		if (unit != patch.unit)
			return *this;
		movementPointsChange = movementPointsChange + patch.movementPointsChange;
		mapX = patch.mapX == -1 ? mapX : patch.mapX;
		mapY = patch.mapY == -1 ? mapY : patch.mapY;
		return *this;
	}
};

