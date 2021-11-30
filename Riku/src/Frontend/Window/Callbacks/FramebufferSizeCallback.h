#pragma once
#define _USE_MATH_DEFINES 
#include <GLFW/glfw3.h>
#include "../../Object.h"
#include "../../Config.h"

namespace front {
	class FramebufferSizeCallback
	{
		float& aspect;
	public:
		FramebufferSizeCallback(float& aspect) : aspect(aspect) {}

		void operator()(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			aspect = (float)width / height;
		}
	};
}

