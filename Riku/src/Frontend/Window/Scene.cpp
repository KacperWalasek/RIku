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
	movingCameraTransform = Transform(glm::vec3((float)map.size() * 0.5f, 10.0f, (float)map.size() * 0.5f), glm::vec3(glm::radians(config.angle), glm::radians(180.0f), 0.0f));

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
	for (int i = 0; i < (int)map.size(); i++)
	{
		for (int j = 0; j < (int)map[i].size(); j++)
		{
			drawTile(map,i,j);
		}
	}
	const auto& unit = state.getUnits();
	for (int i = 0; i < (int)unit.size(); i++) {
        if (i != focusedUnitIndex)
            lightingShader.setVec4("color_mod", 0.7f, 0.7f, 0.7f, 1.0f);
        int x = unit[i]->getMapX();
        int y = unit[i]->getMapY();
        auto transform = front::Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y));
        if(i==focusedUnitIndex)
            handler.tryDraw("main_circle", lightingShader, transform);
		handler.tryDraw(unit[i]->getName(), lightingShader, transform);
		lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	}
    for(auto&& [x,y]: path.path) {
        handler.tryDraw("main_move", lightingShader, Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y)));
    }

	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);

	light.drawCubes(projection, view, fogDensity, movingCameraTransform.position);
}

void front::Scene::drawTile(const std::vector<std::vector<Tile>> &map, int x, int y) {
	if(x==clickPos.first && y==clickPos.second)
		lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	else
		lightingShader.setVec4("color_mod", 0.8f, 0.75f, 0.75f, 1.0f);
	glm::vec3 scale = {.333333f,.333333f,.333333f};
	//draw center
	auto transform = Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y),glm::vec3(),scale);
	if (map[x][y].area.getName() == "wet")
		handler.tryDraw("wet",lightingShader, transform);
	handler.drawGround(map[x][y].ground.getName(), "_flat",lightingShader, transform);
	//draw sides (only flat)
	for(int i=0;i<4;i++) {
		int dx = i%2 ? 0 : i-1;
		int dy = i%2 ? i-2 : 0;
		int dh;
		if((x+dx<0 || x+dx>=(int)map.size()) || y+dy<0 || y+dy>=(int)map[0].size())
			dh=0;
		else
			dh = map[x+dx][y+dy].height - map[x][y].height;
		Transform sideTransform;
		if(dh==0 || std::abs(dh)>=2) {
			sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f,
			                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, 90.0f * i, 0.0f), scale);
			handler.drawGround(map[x][y].ground.getName(), "_flat",lightingShader, sideTransform);
		}
		else if (dh==1){
			sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
			                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
			handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform);
		}
		else if (dh==-1){
			sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f-0.125f,
			                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i + 180.0f, 0.0f), scale);
			handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform);
		}
	}
	//draw corner
	for(int i=0;i<4;i++) {
		int dx = i%2 ? 2-i : i-1;
		int dy = i%2 ? i-2 : i-1;
		int dhx, dhy, dhz;
		{
			int dxt=dx, dyt=dy;
			if(x+dx<0 || x+dx>=(int)map.size())
				dxt=0;
			if(y+dy<0 || y+dy>=(int)map[0].size())
				dyt=0;
			dhx = map[x+dxt][y].height - map[x][y].height;
			dhy = map[x][y+dyt].height - map[x][y].height;
			dhz = map[x+dxt][y+dyt].height - map[x][y].height;
		}
		if(i%2==1)
			std::swap(dhx,dhy);
		uint8_t caseUint=0x0; //____yyxx (bits)
		if(std::abs(dhx)>=2)
			caseUint=0x1;
		else
			caseUint=1+dhx;
		if(std::abs(dhy)>=2)
			caseUint+=0x4;
		else
			caseUint+=0x4*(1+dhy);
		Transform sideTransform;
		switch(caseUint) {
			case 0:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f-0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, 90.0f - 90.0f*i , 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_corner+",lightingShader, sideTransform);
				break;
			case 1:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f-0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i + 90.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform);
				break;
			case 2:
				sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f ,
					(float)y + (float)dy / 3.f), glm::vec3(0.0f, 90.0f * i + 90.0f, 0.0f), { -scale.x,scale.y,scale.z});
				handler.drawGround(map[x][y].ground.getName(), "_double_corner", lightingShader, sideTransform);
				break;
			case 4:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f-0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i+180.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform);
				break;
			case 5:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_flat",lightingShader, sideTransform);
				break;
			case 6:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform);
				break;
			case 8:
				sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f ,
					(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i - 180.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_double_corner", lightingShader, sideTransform);
				break;
			case 9:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i - 90.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform);
				break;
			case 10:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f - 90.0f * i, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_corner-",lightingShader, sideTransform);
				break;
		}
	}

	//draw object
	auto objectTransform = front::Transform({(float)x, (float)map[x][y].height * 0.5f, (float)y});
	handler.tryDraw(map[x][y].biome.getName(), lightingShader, objectTransform);
	if (map[x][y].object)
		handler.tryDraw(map[x][y].object->getName(), lightingShader, objectTransform);
}
