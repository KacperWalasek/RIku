#pragma once
#include "FrontendState.h"
#include "Config.h"
#include "Scene/Window.h"

class GameLogic;
namespace front {
	class Frontend
	{
		GameLogic& logic;
		FrontendState state;
		Window window;
		Config config;
	public:
		Frontend(GameLogic& logic);
		bool update();
	};
}

