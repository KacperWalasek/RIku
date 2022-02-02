#pragma once
#include <GLFW\glfw3.h>

class LoadingWindow
{
	GLFWwindow* window;
public:
	LoadingWindow();
	void destroy();
	void update();
};

