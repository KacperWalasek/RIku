#pragma once
#define _USE_MATH_DEFINES 
#include <GLFW/glfw3.h>
#include "../../Object.h"
#include "../../Config.h"

namespace front {
	class MouseClickCallback
	{
		CEGUI::GUI* activeGUI;
	public:
		MouseClickCallback(CEGUI::GUI* activeGUI) : activeGUI(activeGUI) {}

		void operator()(GLFWwindow* window, int button, int action, int mods)
		{
			activeGUI->on_mouse_click(button, action);
		}
	};
}

