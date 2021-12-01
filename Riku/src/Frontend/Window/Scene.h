#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/gtx/rotate_vector.hpp>
#ifdef _WIN32
#undef max
#undef min
#endif
#include "../Object.h"
#include "../Shader.h"
#include "../GUIFactory.h"
#include "../Config.h"
#include "../Model.h"
#include "Light.h"
#include "../Asset/FAssetHandler.h"

namespace front {
	class Window;
	class Scene
	{
		FrontendState& state;
		Config& config;
		const AssetHandler& handler;

		Transform movingCameraTransform;

		Shader lightingShader;

		float fogDensity = 0.01f;
		int focusedUnitIndex = 0;
		float& aspect;

		Light light;
		CEGUI::GUIFactory fac;
		CEGUI::GUI* activeGUI;
		std::map<std::string, CEGUI::GUI*> guiDic;

		glm::vec2 clickPos;
		friend class MouseClickCallback;

		void init(GLFWwindow* window);
	public:
		Scene(Config& config, GameLogic& logic, FrontendState& state, const AssetHandler& handler, float& aspect);
		void update();//input
		void draw();

		friend class Window;
	};
}

