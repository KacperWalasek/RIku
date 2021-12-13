#include "UnitPatchHandler.h"

std::shared_ptr<IMove> UnitPatchHandler::handlePatch(GameState&, const Patch& patch) const
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
	}
	return nullptr;
}
