#pragma once
#include "IMiniPatchHandler.h"
#include "../../Utils/MiniGameUtils.h"

namespace minigame
{
	class UnitMiniPatchHandler :
		public IMiniPatchHandler
	{
	public:
		virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
		{
			for (auto unitPatch : patch.unitPatches)
			{
				std::shared_ptr<MiniUnit> unit = std::dynamic_pointer_cast<MiniUnit>(MiniGameUtils::getHookable(unitPatch.second.unit));
				unit->movementPoints += unitPatch.second.movementPointsChange;
				if (unit->movementPoints < 0)
					unit->movementPoints = 0;
				// TODO: odhardcodowac 2
				if (unit->movementPoints > 2 * unit->baseMovementPoints)
					unit->movementPoints = 2 * unit->baseMovementPoints;

				if (unitPatch.second.mapX != -1)
					unit->mapX = unitPatch.second.mapX;
				if (unitPatch.second.mapY != -1)
					unit->mapY = unitPatch.second.mapY;
			}

			return nullptr;
		}
	};

}