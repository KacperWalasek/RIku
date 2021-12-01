#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>
#include "../stb_image.h"
#ifdef _WIN32
#undef max
#undef min
#endif
#include "../Config.h"
#include "Scene.h"

namespace front {
	class Window
	{
		Config& config;
		GLFWwindow* window;

		float aspect;
		float lastFrame = 0.0f;
		float deltaTime;

		Scene scene;

		std::optional<glm::vec2> getRelativeCursorPosition();
		void initWindow();
		void setCallbacks();
		void processInput();
	public:
		Window(Config& config, GameLogic& logic, FrontendState& state, const AssetHandler& hadler);
		~Window();
		bool update();
	};
}

