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

		auto& units = unitPatch.second.addedMiniUnits;
		if (units.size() > 0)
			unit->miniunits.insert(unit->miniunits.end(), units.begin(), units.end());
		auto& skills = unitPatch.second.addedSkills;
		if (skills.size() > 0)
			unit->skills.insert(unit->skills.end(), skills.begin(), skills.end());
	}
	return nullptr;
}
