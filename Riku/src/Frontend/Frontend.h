#pragma once
#include "FrontendState.h"
#include "Config.h"
#include "Scene/Scene.h"

class GameLogic;
namespace front {
	class Frontend
	{
		GameLogic& logic;
		FrontendState state;
		Scene scene;
		Config config;
	public:
		Frontend(GameLogic& logic);
		bool update();
	};
}

