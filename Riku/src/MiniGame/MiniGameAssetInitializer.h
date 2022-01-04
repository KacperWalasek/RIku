#pragma once
#include "../GameLogic/Assets/IAssetInitializer.h"

namespace minigame
{
	class MiniGameAssetInitializer : public IAssetInitializer
	{
	public:
		virtual void initAsset(std::shared_ptr<sol::state> lua) const override;
	};

}