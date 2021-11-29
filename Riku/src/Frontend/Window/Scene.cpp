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

front::Scene::Scene(Config& config, GameLogic& logic, FrontendState& state, float& aspect)
	: config(config), fac(logic,state,activeGUI, guiDic, focusedUnitIndex), state(state), aspect(aspect)
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
	//grounds
	groundModels.insert(std::make_pair("grass", Model("models/grounds/grass.obj", 1, 1)));
	groundModels.insert(std::make_pair("sand", Model("models/grounds/sand.obj", 1, 1)));
	groundModels.insert(std::make_pair("stone", Model("models/grounds/stone.obj", 1, 1)));
	groundModels.insert(std::make_pair("wet", Model("models/grounds/water.obj", 1, 1)));
	//biomes
	biomeModels.insert(std::make_pair("forest", Model("models/biomes/forest.blend", 1, -1)));
	//objects
	objectModels.insert(std::make_pair("wood_factory", Model("models/objects/farmhouse_obj.obj", 1, -1)));
	//units
	unitModel = Model("models/units/sara/model/sara.blend", 1, -1);


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
			front::Object object;
			if (map[i][j].area.getName() == "wet")
				object = Object(groundModels["wet"], glm::vec3(i, (float)map[i][j].height * 0.5f, j));
			else
				object = Object(groundModels[map[i][j].ground.getName()], glm::vec3(i, (float)map[i][j].height * 0.5f, j));
			object.Draw(lightingShader);
			if (map[i][j].object && objectModels.count(map[i][j].object->getName())) {
				Object mapObject = Object(objectModels[map[i][j].object->getName()], glm::vec3(i, (float)map[i][j].height * 0.5f, j - 0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.02f, 0.02f));
				mapObject.Draw(lightingShader);
			}
		}
	}
	const auto& unit = state.getUnits();
	for (int i = 0; i < unit.size(); i++) {
		if (i != focusedUnitIndex)
			lightingShader.setVec4("color_mod", 0.7f, 0.7f, 0.7f, 1.0f);
		int x = unit[i]->getMapX();
		int y = unit[i]->getMapY();
		front::Object object = front::Object(unitModel, glm::vec3(x, (float)map[x][y].height * 0.5f, y), glm::vec3(-90.0f, 0.0f, 180.0f), glm::vec3(0.01f, 0.01f, 0.01f));
		object.Draw(lightingShader);
		lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);

	}

	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);

	light.drawCubes(projection, view, fogDensity, movingCameraTransform.position);
}
