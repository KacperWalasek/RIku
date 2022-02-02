#pragma once
#include "../Shader.h"

struct GLFWwindow;
class LoadingWindow
{
	GLFWwindow* window;
	Shader shader;
	unsigned texture, VAO, VBO, EBO;
public:
	LoadingWindow();
	void destroy();
	void update();
};

