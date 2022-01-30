#define _USE_MATH_DEFINES 
#include "Scene.h"
#include <iostream>
#include <iomanip>
#include <stb_image/stb_image.h>
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
#include "../FrustumCulling.h"

constexpr uint8_t playerColors[][3]={
		{255,0,0},
		{0,0,255},
		{0,255,0},
		{255,255,255},
		{0,0,0},
		{255,255,0},
		{255,0,255},
		{0,255,255},
		{255,127,0},
		{255,0,127},
		{127,255,0},
		{0,255,127},
		{127,0,255},
		{0,127,255},
};

front::Scene::Scene(Config& config, GameLogic& logic, FrontendState& state, const AssetHandler& handler, float& aspect)
	: config(config), fac(logic,state,activeGUI, lastActiveGUI, guiDic, focusedUnitIndex), state(state), aspect(aspect), handler(handler), path({},0)
{}

front::Scene::~Scene()
{
	for (auto p : guiDic)
		delete p.second;
}
void front::Scene::update()
{
	CEGUI::GUIUpdate::CoreUpdate(state, activeGUI, guiDic, focusedUnitIndex, focusedSkill, movingCameraTransform, lastActiveGUI);
	draw();
	CEGUI::GUI::drawMultiple(guiDic, activeGUI);
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
	guiDic.insert(std::pair("OptionsMenu", fac.GetOptionsMenu()));
	guiDic.insert(std::pair("NewGameMenu", fac.GetNewGameMenu()));
	guiDic.insert(std::pair("JoinGameMenu", fac.GetJoinGameMenu()));
	guiDic.insert(std::pair("BuildingUI", fac.GetBuildingUI()));
	guiDic.insert(std::pair("RecruitingUI", fac.GetRecruitingUI()));
	guiDic.insert(std::pair("Popup", fac.GetPopup()));
	guiDic.insert(std::pair("SetNamePopup", fac.GetSetNamePopup()));
	guiDic.insert(std::pair("MiniGameUI", fac.GetMiniGameUI()));
	guiDic.insert(std::pair("LoadingScreen", fac.GetLoadingScreen()));
	guiDic["MainMenu"]->show();
	activeGUI = guiDic["SetNamePopup"];
	activeGUI->show();
	CEGUI::GUIUpdate::UpdateUIButtons(guiDic);
}

void front::Scene::drawInit(glm::mat4& projection, glm::mat4& view) {
	float dayPart = 1;
	if (fogDensity >= 0.05f)
		glClearColor(dayPart * 0.7f, dayPart * 0.7f, dayPart * 0.7f, 1.0f);
	else
	{
		float fog_per = fogDensity / 0.05f;
		glClearColor(dayPart * (0.2f + 0.5f * fog_per), dayPart * 0.7f, dayPart * (1.0f - 0.3f * fog_per), 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//
	projection = glm::perspective(glm::radians(config.fov), aspect, 0.1f, 100.0f);
	view = movingCameraTransform.calculateViewMatrix();
	frustum = Frustum(movingCameraTransform, aspect, config.fov, 0.1f, 100.0f);
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
}


void front::Scene::drawMiniGame() {
	const auto& map = state.getMiniMap();
	const auto& units = state.getMiniUnits();
	if (focusedUnitIndex >= units.size())
		focusedUnitIndex = -1;
	if (focusedUnitIndex < 0 && focusedUnitIndex >= units.size())
		path = Path({}, 0);
	for(int i=0;i<(int)map.size();i++) {
		for(int j=0;j<(int)map[i].size();j++) {
			auto transform = front::Transform(glm::vec3((float)i, 0.0f, (float)j));
			handler.drawGround("grass", "_flat", lightingShader, transform, frustum);
			if(map[i][j].unit) {
				const auto* unit = map[i][j].unit.get();
				auto&& color = playerColors[unit->getOwner()];
				if(focusedUnitIndex == -1 || unit!=units[focusedUnitIndex].get())
					lightingShader.setVec4("color_mod", color[0]/360.f, color[1]/360.f, color[2]/360.f, 1.0f);
				else {
					lightingShader.setVec4("color_mod", color[0]/255.f, color[1]/255.f, color[2]/255.f, 1.0f);
					if(path.path.empty())
						handler.tryDraw("main_circle", lightingShader, transform, frustum);
				}
				handler.tryDraw(unit->getName(), lightingShader, transform, frustum);
				lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
	for (auto& tile : path.path) {
		if(&tile==&path.path.front())
			continue;
		auto&& [x, y] = tile.tile;
		if(&tile==&path.path.back()) {
			if(tile.reachable)
				handler.tryDraw("main_circle_reach", lightingShader, Transform(glm::vec3((float)x, .0f, (float)y)), frustum);
			else
				handler.tryDraw("main_circle", lightingShader, Transform(glm::vec3((float)x, .0f, (float)y)), frustum);
		}
		else {
			if (tile.reachable)
				handler.tryDraw("main_move", lightingShader,
				                Transform(glm::vec3((float) x, .0f, (float) y)), frustum);
			else
				handler.tryDraw("main_move_not", lightingShader,
				                Transform(glm::vec3((float) x, .0f, (float) y)), frustum);
		}
	}

	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
}

void front::Scene::drawGame() {
	const auto& map = state.getMap();
	const auto& units = state.getUnits();
	if (focusedUnitIndex >= units.size())
		focusedUnitIndex = -1;
	if (focusedUnitIndex < 0 && focusedUnitIndex >= units.size())
		path = Path({}, 0);
	// render the loaded models
	//draw tiles
	auto& meshes = state.getMapMeshes(handler);
	for (auto& pair : meshes)
	{
		Model model;
		model.meshes.push_back(pair.second);
		Object obj(model);
		obj.Draw(lightingShader);
	}
	for (int i = 0; i < (int)map.size(); i++)
	{
		for (int j = 0; j < (int)map[i].size(); j++)
		{
			drawTile(map,i,j);
		}
	}
	/*const auto& unit = state.getUnits();
	for (int i = 0; i < (int)unit.size(); i++) {
        if (i != focusedUnitIndex)
            lightingShader.setVec4("color_mod", 0.7f, 0.7f, 0.7f, 1.0f);
        int x = unit[i]->getMapX();
        int y = unit[i]->getMapY();
        auto transform = front::Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y));
        if(i==focusedUnitIndex) {
			if(!path.path.empty()) {
				auto&& [tx,ty] = path.path.back().tile;
				auto pathTransform = front::Transform(glm::vec3((float)tx, (float)map[tx][ty].height * 0.5f, (float)ty));
				if(path.path.back().reachable)
					handler.tryDraw("main_circle_reach", lightingShader, pathTransform, frustum);
				else
					handler.tryDraw("main_circle", lightingShader, pathTransform, frustum);
			}
			else
		        handler.tryDraw("main_circle", lightingShader, transform, frustum);
        }
		handler.tryDraw(unit[i]->getName(), lightingShader, transform, frustum);
		lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	}*/
    for(auto& tile: path.path) {
	    if(&tile==&path.path.front())
		    continue;
	    auto&& [x, y] = tile.tile;
		if(&tile==&path.path.back()) {
			if(tile.reachable)
				handler.tryDraw("main_circle_reach", lightingShader, Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f+0.3f, (float)y)), frustum);
			else
				handler.tryDraw("main_circle", lightingShader, Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f+0.3f, (float)y)), frustum);
		}
		else {
			if (tile.reachable)
				handler.tryDraw("main_move", lightingShader,
				                Transform(glm::vec3((float) x, (float) map[x][y].height * 0.5f, (float) y)), frustum);
			else
				handler.tryDraw("main_move_not", lightingShader,
				                Transform(glm::vec3((float) x, (float) map[x][y].height * 0.5f, (float) y)), frustum);
		}
    }

	//return to default value
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
}

void front::Scene::draw()
{

	drawInit(projection, view);
	// render the loaded models
	//draw tiles
	if (!state.isInGame())
		return;
	if(state.isInMiniGame())
		drawMiniGame();
	else
		drawGame();
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
	
	/*//draw center
	auto transform = Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f, (float)y),glm::vec3(),scale);
	if (map[x][y].area.getName() == "wet")
		handler.tryDraw("wet",lightingShader, transform, frustum);
	handler.drawGround(map[x][y].ground.getName(), "_flat",lightingShader, transform, frustum);
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
			handler.drawGround(map[x][y].ground.getName(), "_flat",lightingShader, sideTransform, frustum);
		}
		else if (dh==1){
			sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
			                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
			handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform, frustum);
		}
		else if (dh==-1){
			sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f-0.125f,
			                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i + 180.0f, 0.0f), scale);
			handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform, frustum);
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
				handler.drawGround(map[x][y].ground.getName(), "_corner+",lightingShader, sideTransform, frustum);
				break;
			case 1:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f-0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i + 90.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform, frustum);
				break;
			case 2:
				sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f ,
					(float)y + (float)dy / 3.f), glm::vec3(0.0f, 90.0f * i + 90.0f, 0.0f), { -scale.x,scale.y,scale.z});
				handler.drawGround(map[x][y].ground.getName(), "_double_corner", lightingShader, sideTransform, frustum);
				break;
			case 4:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f-0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i+180.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform, frustum);
				break;
			case 5:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_flat",lightingShader, sideTransform, frustum);
				break;
			case 6:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform, frustum);
				break;
			case 8:
				sideTransform = Transform(glm::vec3((float)x + (float)dx / 3.f, (float)map[x][y].height * 0.5f ,
					(float)y + (float)dy / 3.f), glm::vec3(0.0f, -90.0f * i - 180.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_double_corner", lightingShader, sideTransform, frustum);
				break;
			case 9:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f * i - 90.0f, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_slope",lightingShader, sideTransform, frustum);
				break;
			case 10:
				sideTransform = Transform(glm::vec3((float) x + (float) dx / 3.f, (float) map[x][y].height * 0.5f+0.125f,
				                                    (float) y + (float) dy / 3.f), glm::vec3(0.0f, -90.0f - 90.0f * i, 0.0f), scale);
				handler.drawGround(map[x][y].ground.getName(), "_corner-",lightingShader, sideTransform, frustum);
				break;
		}

	}*/
	//draw clifs
	for (int i = 0; i < 4; i++) {
		int dx = i % 2 == 0 ? 0 : 2 - i;
		int dy = i % 2 == 0 ? i - 1 : 0;
		int dh;
		if ((x + dx < 0 || x + dx >= (int)map.size()) || y + dy < 0 || y + dy >= (int)map[0].size())
			dh = 0;
		else
			dh = map[x + dx][y + dy].height - map[x][y].height;
		
		if (dh < -1)
		{
			int side = i < 2 ? 1 : -1;
			for (int j = dh+1; j < 1; j++)
			{
				for (int k = -1; k < 2; k++)
				{
					int zX = x - k * abs(dy);
					int zY = y + k * abs(dx);
					float yScale = 1 / 2.f;
					float yTransition = 0.25f;
					if (j == 0 && zX >= 0 && zY >= 0 && zX < map.size() && zY < map[0].size()
						&& map[zX][zY].height - map[x][y].height == -1)
					{
						yScale = 1 / 4.f;
						yTransition = 0.375f;
					}
					Transform clifTransform = Transform(glm::vec3(
						(float)x + 0.5f * side * (i % 2) + (i%2 - 1)*k/3.f, 
						(float)map[x][y].height * 0.5f + 0.5f * j - yTransition, 
						(float)y + (i % 2 - 1) * side * 0.5 + (i % 2) * k/3.f) ,
						glm::vec3(90.0f, 0.0f, 90.0f * i), glm::vec3(1 / 3.f, yScale, 1 / 3.f));
					handler.drawGround(map[x][y].ground.getName(), "_cliff", lightingShader, clifTransform, frustum);
				}
			}
		}
		
	}
	//draw object
	auto objectTransform = front::Transform({(float)x, (float)map[x][y].height * 0.5f, (float)y});
	//handler.tryDraw(map[x][y].biome.getName(), lightingShader, objectTransform);
	if (map[x][y].object)
		handler.tryDraw(map[x][y].object->getName(), lightingShader, objectTransform, frustum);
	const auto& units = state.getUnits();
	if (map[x][y].unit) {
		const auto& unit = map[x][y].unit;
		auto&& color = playerColors[unit->getOwner()];
		auto transform = front::Transform(glm::vec3((float)x, (float)map[x][y].height * 0.5f+0.3f, (float)y));
		if (focusedUnitIndex == -1 || unit->getId() != units[focusedUnitIndex]->getId())
			lightingShader.setVec4("color_mod", color[0] / 360.f, color[1] / 360.f, color[2] / 360.f, 1.0f);
		else
		{
			lightingShader.setVec4("color_mod", color[0] / 255.f, color[1] / 255.f, color[2] / 255.f, 1.0f);
			if(path.path.empty())
				handler.tryDraw("main_circle", lightingShader, transform, frustum);
		}
		handler.tryDraw(unit->getName(), lightingShader, transform, frustum);
		lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
	}
}
