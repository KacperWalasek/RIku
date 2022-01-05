#pragma once
#include "../GameLogic/Assets/AssetHandler.h"

namespace minigame
{
	class MiniGameAssets
	{
		logic::AssetHandler handler;
	public:
		MiniGameAssets();
		std::map<std::string, logic::Asset> units;

		void initialize(std::string path);
	};
}
