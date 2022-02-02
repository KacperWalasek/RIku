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
#include "../FrustumCulling.h"

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
		std::string focusedSkill = "";
		float& aspect;

		Light light;
		CEGUI::GUIFactory fac;
		CEGUI::GUI* activeGUI;
		CEGUI::GUI* lastActiveGUI;
		std::map<std::string, CEGUI::GUI*> guiDic;
		glm::mat4 projection, view;

		std::pair<int, int> clickPos;
        Path path;
		Frustum frustum;
		friend class MouseClickCallback;
		bool isFocused = true;

		void init(GLFWwindow* window);
		void drawTile(const std::vector<std::vector<Tile>> &map, int x, int y);
		void drawGame();
		void drawMiniGame();
		void drawInit(glm::mat4& projection, glm::mat4& view);
	public:
		bool isGameActive = false;
		const glm::mat4& getProjection() const {return projection;}
		const glm::mat4& getView() const {return view;}
		const Transform& getCamera() const {return movingCameraTransform;}
		const Frustum& getFrustum() const {return frustum;}
		Scene(Config& config, GameLogic& logic, FrontendState& state, const AssetHandler& handler, float& aspect);
		~Scene();
		void update();//input
		void draw();

		friend class Window;
	};
}

