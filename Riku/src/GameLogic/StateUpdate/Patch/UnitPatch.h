#pragma once
#include <memory>

class Unit;
class UnitPatch
{
public:
	UnitPatch(std::shared_ptr<Unit> unit, int movementPointsChange)
		 : unit(unit), movementPointsChange(movementPointsChange)
	{}
	std::shared_ptr<Unit> unit;
	int movementPointsChange;

	UnitPatch& operator+=(const UnitPatch& patch)
	{
		if (unit != patch.unit)
			return *this;
		movementPointsChange = movementPointsChange + patch.movementPointsChange;
		return *this;
	}
};

