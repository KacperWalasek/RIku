#pragma once
#define _USE_MATH_DEFINES 
#include <GLFW/glfw3.h>
#include "../../Object.h"
#include "../../Config.h"

namespace front {
	class MousePositionCallback
	{
		CEGUI::GUI* activeGUI;
	public:
		MousePositionCallback(CEGUI::GUI* activeGUI) : activeGUI(activeGUI) {}
		
		void operator()(GLFWwindow* window, double xpos, double ypos)
		{
			activeGUI->on_mouse_pos(xpos, ypos);
		}
	};
}

