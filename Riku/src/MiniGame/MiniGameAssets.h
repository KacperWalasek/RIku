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
		std::map<std::string, logic::Asset> skills;
		void initialize(std::string path);
		const logic::AssetHandler& getHandler();
	};
}
