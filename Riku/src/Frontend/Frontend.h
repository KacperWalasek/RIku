#pragma once
#include "FrontendState.h"
#include "Config.h"
#include "Window/Window.h"
#include "Asset/FAssetHandler.h"

class GameLogic;
namespace front {
	class Frontend
	{
	public:
		GameLogic& logic;
		FrontendState state;
		AssetHandler assetHandler;
		Window window;
		Config& config;
	public:
		Frontend(GameLogic& logic, Config& config);
		bool update();
	};
}

