#define _USE_MATH_DEFINES 
#include "Scene.h"
#include <iostream>
#include "../stb_image.h"
#include <cmath>
#ifdef _WIN32
	#undef max
	#undef min
#endif
#include "Callbacks/ScrollCallback.h"
#include "Callbacks/FramebufferSizeCallback.h"
#include "Callbacks/MousePositionCallback.h"
#include "Callbacks/MouseClickCallback.h"
#include "Callbacks/KeyCallback.h"

front::Scene::Scene(Config& config, GameLogic& logic, FrontendState& state, const AssetHandler& handler, float& aspect)
	: config(config), fac(logic,state,activeGUI, guiDic, focusedUnitIndex), state(state), aspect(aspect), handler(handler)
{}

void front::Scene::update()
{
	draw();
	for (auto p : guiDic)
	{
		p.second->draw(); // wyswietla tylko gui nawet jak nie sa poukrywane
	}
}

void front::Scene::init(GLFWwindow* window)
{
	lightingShader.init("../shaders/phong-vertex.shader", "../shaders/phong-fragment.shader");
	light.init();

	//set camera transform
	const auto& map = state.getMap();
	movingCameraTransform = Transform(glm::vec3(map.size() * 0.5f, 10.0f, map.size() * 0.5f), glm::vec3(glm::radians(config.angle), glm::radians(180.0f), 0.0f));

	// shader configuration
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

	fac.init(window);
	guiDic.insert(std::pair("GameUI", fac.GetGameUI()));
	guiDic.insert(std::pair("MainMenu", fac.GetMainMenu()));
	guiDic.insert(std::pair("BuildingUI", fac.GetBuildingUI()));
	activeGUI = guiDic["GameUI"];
	activeGUI->show();
}

void front::Scene::draw()
{
	float dayPart = 0.5f;
	if (fogDensity >= 0.05f)
		glClearColor(dayPart * 0.7f, dayPart * 0.7f, dayPart * 0.7f, 1.0f);
	else
	{
		float fog_per = fogDensity / 0.05f;
		glClearColor(dayPart * (0.2f + 0.5f * fog_per), dayPart * 0.7f, dayPart * (1.0f - 0.3f * fog_per), 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//
	glm::mat4 projection = glm::perspective(glm::radians(config.fov), aspect, 0.1f, 100.0f);
	glm::mat4 view = movingCameraTransform.calculateViewMatrix();
	//shader initialization
	lightingShader.use();
	lightingShader.setMat4("projection", projection);
	lightingShader.setMat4("view", view);
	lightingShader.setVec3("viewPos", movingCameraTransform.position);
	lightingShader.setFloat("material.shininess", 32.0f);
	//default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	//fog parameters
	lightingShader.setFloat("fog_density",fogDensity);
	lightingShader.setVec4("fog_color", 0.7f * dayPart, 0.7f * dayPart, 0.7f * dayPart, 1.0f);

	//Setting lights
	light.apply(lightingShader, dayPart);

	// render the loaded models
	//draw tiles
	const auto& map = state.getMap();
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if(i==int(clickPos.x+0.5f) && j==int(clickPos.y+0.5f))
				lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
			else
				lightingShader.setVec4("color_mod", 0.8f, 0.75f, 0.75f, 1.0f);
			auto transform = front::Transform(glm::vec3((float)i, (float)map[i][j].height * 0.5f, (float)j));
			if (map[i][j].area.getName() == "wet")
				handler.tryDraw("wet", lightingShader, transform);
			else
				handler.tryDraw(map[i][j].ground.getName(), lightingShader, transform);
			if (map[i][j].object) 
				handler.tryDraw(map[i][j].object->getName(), lightingShader, transform);
				/*front::Object mapObject = front::Object(front::objectModels[map[i][j].object->getName()],glm::vec3(i,(float)map[i][j].height*0.5f,j - 0.25f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.02f,0.02f,0.02f));
				mapObject.Draw(lightingShader);*/
		}
	}
	const auto& unit = state.getUnits();
	for (int i = 0; i < unit.size(); i++) {
		if (i != focusedUnitIndex)
			lightingShader.setVec4("color_mod", 0.7f, 0.7f, 0.7f, 1.0f);
		int x = unit[i]->getMapX();
		int y = unit[i]->getMapY();
		auto transform = front::Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y));
		handler.tryDraw(unit[i]->getName(), lightingShader, transform);
		lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);

	}

	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);

	light.drawCubes(projection, view, fogDensity, movingCameraTransform.position);
}