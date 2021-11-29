#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Config.h"
#include <vector>
#include <glm/gtx/rotate_vector.hpp>
#include "../Object.h"
#include "../Shader.h"
#include "../GUIFactory.h"
#ifdef _WIN32
#undef max
#undef min
#endif
#include "../Model.h"
namespace front {
	class Scene
	{
		GameLogic& logic;
		FrontendState& state;
		uint16_t NR_SPOT_LIGHTS = 1;
		GLFWwindow* window;
		Config& config;

		Transform movingCameraTransform;
		float aspect;
		std::vector<glm::vec3> pointLightPositions;

		Shader lightingShader;
		Shader lightCubeShader;

		unsigned int VBO;
		unsigned int lightCubeVAO;
		float lastFrame = 0.0f;
		float deltaTime;
		float fogDensity = 0.01f;
		float spotLightAngle = 0.0f;
		int focusedUnitIndex = 0;

		CEGUI::GUIFactory fac;
		CEGUI::GUI* activeGUI;
		std::map<std::string, CEGUI::GUI*> guiDic;

		std::map<std::string, Model> groundModels;
		std::map<std::string, Model> biomeModels;
		std::map<std::string, Model> objectModels;
		Model unitModel;

		void initWindow();
		void setCallbacks();
		std::optional<glm::vec2> getRelativeCursorPosition();
		void processInput();
	public:
		Scene(Config& config, GameLogic& logic, FrontendState& state);
		~Scene();
		bool update();//input
		void draw();

	};
}

