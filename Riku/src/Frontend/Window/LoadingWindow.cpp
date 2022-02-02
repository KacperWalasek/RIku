#include "LoadingWindow.h"
#include <iostream>

LoadingWindow::LoadingWindow()
{
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	window = glfwCreateWindow(400, 200, "Riku", nullptr, nullptr); 
	if (window == nullptr) {
		std::cerr << "Creating loading window failed" << std::endl;
	}
}

void LoadingWindow::destroy()
{
	glfwDestroyWindow(window);
}

void LoadingWindow::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

