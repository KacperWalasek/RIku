#include "UnitPatchHandler.h"
#include "../../Unit/Unit.h"

std::shared_ptr<IAction> UnitPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
	for (auto unitPatch : patch.unitPatches)
	{
		std::shared_ptr<Unit> unit = unitPatch.second.unit;
		
		unit->movementPoints += unitPatch.second.movementPointsChange;
		if (unit->movementPoints < 0)
			unit->movementPoints = 0;
		// TODO: odhardcodowac 2
		if (unit->movementPoints > 2 * unit->baseMovementPoints)
			unit->movementPoints = 2 * unit->baseMovementPoints;

		if (unitPatch.second.mapX > -1)
			unit->mapX = unitPatch.second.mapX;
		if (unitPatch.second.mapY > -1)
			unit->mapY = unitPatch.second.mapY;
	}
	return nullptr;
}
