#pragma once
#include "IMiniPatchHandler.h"
#include "../../Utils/MiniGameUtils.h"
namespace minigame
{
	class TileMiniPatchHandler :
		public IMiniPatchHandler
	{
	public:
		virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
		{
			for (auto& tilePatch : patch.tilePatches)
			{
				MiniTile& tile = state.map[tilePatch.first.first][tilePatch.first.second];
				if (tilePatch.second.removeUnit)
					tile.unit = nullptr;
				if (tilePatch.second.unit != "")
					tile.unit = std::dynamic_pointer_cast<MiniUnit>(MiniGameUtils::getHookable(tilePatch.second.unit));
			}
			return nullptr;
		}
	};
}
