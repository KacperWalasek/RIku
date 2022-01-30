//
// Created by kamil-hp on 30.01.2022.
//

#ifndef RIKU_FOCUSCALLBACK_H
#define RIKU_FOCUSCALLBACK_H
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include "../../Object.h"
#include "../../Config.h"
#include "../../GUI.h"


namespace front {
	class FocusCallback{
		CEGUI::GUI* activeGUI;
		bool& isFocused;
	public:
		FocusCallback(CEGUI::GUI* activeGUI, bool& focus) : activeGUI(activeGUI), isFocused(focus) {}
		void operator()(GLFWwindow* window, int focused) {
			isFocused=focused;
			std::cout << focused;
		}
	};
}

#endif //RIKU_FOCUSCALLBACK_H
