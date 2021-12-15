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
#include "../GUIUpdate.h"
#include "../DrawManager/ObjectDrawManager.h"

front::Scene::Scene(Config& config, GameLogic& logic, FrontendState& state, const AssetHandler& handler, float& aspect)
	: config(config), fac(logic,state,activeGUI, guiDic, focusedUnitIndex), state(state), aspect(aspect), handler(handler), path({},0)
{}

front::Scene::~Scene()
{
	for (auto p : guiDic)
		delete p.second;
}
void front::Scene::update()
{
	CEGUI::GUIUpdate::CoreUpdate(state, guiDic, focusedUnitIndex);
	draw();
	CEGUI::GUI::drawMultiple(guiDic);
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
	guiDic.insert(std::pair("OptionsMenu", fac.GetOptionsMenu()));
	guiDic.insert(std::pair("RecruitingUI", fac.GetRecruitingUI()));
	guiDic.insert(std::pair("PlayerChangedUI", fac.GetPlayerChangedUI()));
	activeGUI = guiDic["MainMenu"];
	activeGUI->show();
	CEGUI::GUIUpdate::UpdateUIButtons(guiDic);
}

void prepareShader(Shader& shader, float dayPart, const front::Transform& camera, float fogDensity, const glm::mat4& projection, const glm::mat4& view) {
    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setVec3("viewPos", camera.position);
    shader.setFloat("material.shininess", 32.0f);
    //default value
    shader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
    //fog parameters
    shader.setFloat("fog_density",fogDensity);
    shader.setVec4("fog_color", 0.7f * dayPart, 0.7f * dayPart, 0.7f * dayPart, 1.0f);
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
    prepareShader(lightingShader, dayPart, movingCameraTransform, fogDensity, projection, view);

	//Setting lights
	//light.apply(lightingShader, dayPart);
    light.apply(massShader, dayPart);

	// render the loaded models
	//draw tiles
	const auto& map = state.getMap();
	for (int i = 0; i < (int)map.size(); i++)
	{
		for (int j = 0; j < (int)map[i].size(); j++)
		{
            glm::vec4 color;
            if(i==clickPos.first && j==clickPos.second)
                color = {1.0f, 1.0f, 1.0f, 1.0f};
            else
                color = {0.75f, 0.75f, 0.75f, 1.0f};
			auto transform = front::Transform(glm::vec3((float)i, (float)map[i][j].height * 0.5f, (float)j));
			if (map[i][j].area.getName() == "wet")
				handler.tryDraw("wet", massShader, transform, color);
			handler.tryDraw(map[i][j].ground.getName(), massShader, transform, color);
            handler.tryDraw(map[i][j].biome.getName(), massShader, transform, color);
			if (map[i][j].object) 
				handler.tryDraw(map[i][j].object->getName(), massShader, transform, color);
            /*if(map[i][i].resource!=-1)
                handler.tryDraw(map[i][j].resource)*/
		}
	}
	const auto& unit = state.getUnits();
	for (int i = 0; i < (int)unit.size(); i++) {
        glm::vec4 color;
        if (i != focusedUnitIndex)
            color = {0.7f, 0.7f, 0.7f, 1.0f};
        else
            color = {1.0f, 1.0f, 1.0f, 1.0f};
        int x = unit[i]->getMapX();
        int y = unit[i]->getMapY();
        auto transform = front::Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y));
        if(i==focusedUnitIndex)
            handler.tryDraw("main_circle", lightingShader, transform); //TODO: for AssetTextures
		handler.tryDraw(unit[i]->getName(), lightingShader, transform, color);
	}
    for(auto&& [x,y]: path.path) {
        handler.tryDraw("main_move", lightingShader, Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y)));
    }
    ObjectDrawManager::draw(massShader);

	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);

	light.drawCubes(projection, view, fogDensity, movingCameraTransform.position);
}
