#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <filesystem>
#include "Frontend/Shader.h"
#include "Frontend/stb_image.h"
#include "Frontend/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Frontend/Model.h"
#include "Frontend/Object.h"
#include "Frontend/Config.h"
#include "GameLogic/Assets/Asset.h"
#include "Frontend/GUI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/FrontendCommunicator/Responses/MapResponse.h"

#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#undef max
#undef min
#else
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#endif
#include <cmath>
#include <optional>

//https://learnopengl.com/Getting-started (CC-BY-NC) was used to help writing the code
float spotLightAngle=0.0f;

front::Transform movingCameraTransform;

bool firstMouse=true;
constexpr uint16_t NR_POINT_LIGHTS=9;
constexpr uint16_t NR_SPOT_LIGHTS=1;

// lighting
constexpr int SRC_WIDTH=1024;
constexpr int SRC_HEIGHT=768;
constexpr float DAY_LENGTH=30.0f;

std::vector<Model> tileTypeModels;
std::vector<Model> unitTypeModels;

struct TileType
{
	int level;
	int type; //0 - grass, 1 - water
};
struct Unit
{
	int type; //0 - Sara, 1 - assassin
	int x;
	int y;
	explicit Unit(int type=0, int x=0, int y=0): type(type), x(x), y(y) {}
};

namespace front
{
	float aspect;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	const glm::vec3 Zero=glm::vec3(0.0f);
	const glm::vec3 One=glm::vec3(1.0f);
	float fogDensity=0.01f; //to-change
	float dayPhase=0.6f;
	int focusedUnit=0;
	std::vector<std::vector<TileType> > tiles;
	std::vector<Unit> units;
	std::vector<Object> gridObjects;
	bool isGridOn=false;
	unsigned int lightCubeVAO;
	std::vector<glm::vec3> pointLightPositions;
	CEGUI::GUI my_gui;
	Config config;
	GLFWwindow* initWindow();
	std::optional<glm::vec2> getRelativeCursorPosition(GLFWwindow* window){
		double x,y;
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glfwGetCursorPos(window,&x, &y);
		x/=width;
		y/=height;
		if(x>=0 && x<=1 && y>=0 && y<=1)
			return glm::vec2(x,y);
		return {};
	}
}

//1 directional light, 16 point lights and spotlights
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	front::aspect=(float)width/height;
}
//function for processing input
void processInput(GLFWwindow *window)
{
	//used for keys which are pressed continuously
	float rotSpeed = M_PI*front::deltaTime;
	float moveSpeed = 1.5f*std::sqrt(movingCameraTransform.position.y)*front::deltaTime;
	float scrollSpeed = 10.0f*front::deltaTime;
	float dx=0.0f,dy=0.0f;
	auto optCursorPos=front::getRelativeCursorPosition(window);
	//camera move
	if(optCursorPos.has_value()) {
		auto cursorPos = optCursorPos.value();
		if (cursorPos.x < 0.1f) {
			dx = 1.0f;
			dy = 1.0f - 2.0f * cursorPos.y;
		} else if (cursorPos.x > 0.9f) {
			dx = -1.0f;
			dy = 1.0f - 2.0f * cursorPos.y;
		} else if (cursorPos.y < 0.1f) {
			dy = 1.0f;
			dx = 1.0f - 2.0f * cursorPos.x;
		} else if (cursorPos.y > 0.9f) {
			dy = -1.0f;
			dx = 1.0f - 2.0f * cursorPos.x;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		movingCameraTransform.position+=glm::rotateY(glm::vec3(0.0,0.0,-moveSpeed),0.0f*glm::radians(movingCameraTransform.rotation.y));
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		movingCameraTransform.position+=glm::rotateY(glm::vec3(0.0,0.0,moveSpeed),0.0f*glm::radians(movingCameraTransform.rotation.y));
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		movingCameraTransform.position+=glm::rotateY(glm::vec3(-moveSpeed,0.0,0.0),0.0f*glm::radians(movingCameraTransform.rotation.y));
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		movingCameraTransform.position+=glm::rotateY(glm::vec3(moveSpeed,0.0,0.0),0.0f*glm::radians(movingCameraTransform.rotation.y));
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		movingCameraTransform.rotation.y-=moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		movingCameraTransform.rotation.y+=moveSpeed;
	//process zoom
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		if(movingCameraTransform.position.y>front::config.minZoomHeight)
			movingCameraTransform.position+=glm::rotateX(glm::vec3(0.f,-scrollSpeed,0.f),(float)M_PI_4-movingCameraTransform.rotation.x*.25f);
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		if(movingCameraTransform.position.y<front::config.maxZoomHeight)
			movingCameraTransform.position+=glm::rotateX(glm::vec3(0.f,scrollSpeed,0.f),(float)M_PI_4-movingCameraTransform.rotation.x*.25f);
	if(movingCameraTransform.position.y<front::config.minZoomHeight)
		movingCameraTransform.position.y=front::config.minZoomHeight;
	if(movingCameraTransform.position.y>front::config.maxZoomHeight)
		movingCameraTransform.position.y=front::config.maxZoomHeight;
	//rotation
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		movingCameraTransform.rotation.y+=rotSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		movingCameraTransform.rotation.y-=rotSpeed;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//key - key code (can be GLFW_KEY_UNKNOWN)
	//scancode - unique for each key
	//action - GLFW_PRESS, GLFW_REPEAT, GLFW_RELEASE
	//mods - GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER, GLFW_MOD_CAPS_LOCK, GLFW_MOD_NUM_LOCK
	if(action==GLFW_RELEASE)
		;
	if(action==GLFW_PRESS)
	{
		front::my_gui.on_key_press(key);
		switch(key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;
			case GLFW_KEY_W:
				front::units[front::focusedUnit].y=std::max(0,front::units[front::focusedUnit].y-1);
				break;
			case GLFW_KEY_S:
				front::units[front::focusedUnit].y=std::min((int)front::tiles[0].size()-1,front::units[front::focusedUnit].y+1);
				break;
			case GLFW_KEY_A:
				front::units[front::focusedUnit].x=std::max(0,front::units[front::focusedUnit].x-1);
				break;
			case GLFW_KEY_D:
				front::units[front::focusedUnit].x=std::min((int)front::tiles.size()-1,front::units[front::focusedUnit].x+1);
				break;
			case GLFW_KEY_G:
				front::isGridOn=!front::isGridOn;
				break;
			case GLFW_KEY_1:
				front::focusedUnit=0;
				break;
			case GLFW_KEY_2:
				front::focusedUnit=1;
				break;
			case GLFW_KEY_3:
				front::focusedUnit=2;
				break;
			case GLFW_KEY_4:
				front::focusedUnit=3;
				break;
			case GLFW_KEY_5:
				front::focusedUnit=4;
				break;
			default:
				break;
		}
	}
}

void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	front::my_gui.on_mouse_pos(xpos, ypos);
	//TODO

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	if((movingCameraTransform.position.y>front::config.minZoomHeight || yoffset<0.0f) && (movingCameraTransform.position.y<front::config.maxZoomHeight || yoffset>0.0f) )
		movingCameraTransform.position-=glm::rotateX(glm::vec3(0.f,yoffset*.5f,0.f),(float)M_PI_4-movingCameraTransform.rotation.x*.25f);
	else
		movingCameraTransform.position.y=std::min(40.0f,std::max(3.0f,movingCameraTransform.position.y));
}

void drawScene(Shader& lightingShader, Shader& lightCubeShader, float currentFrame){
	//calculating
	front::dayPhase+=front::deltaTime/DAY_LENGTH;

	float dayPart=0.5f*(1.0f+std::sin(M_PI*2.0f*front::dayPhase));
	if(front::fogDensity>=0.05f)
		glClearColor(dayPart*0.7f, dayPart*0.7f, dayPart*0.7f, 1.0f);
	else
	{
		float fog_per=front::fogDensity/0.05f;
		glClearColor(dayPart*(0.2f+0.5f*fog_per), dayPart*0.7f, dayPart*(1.0f-0.3f*fog_per), 1.0f);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//
	glm::mat4 projection = glm::perspective(glm::radians(front::config.fov), front::aspect, 0.1f, 100.0f);
	glm::mat4 view = movingCameraTransform.calculateViewMatrix();
	//shader initialization
	lightingShader.use();
	lightingShader.setMat4("projection", projection);
	lightingShader.setMat4("view", view);
	lightingShader.setVec3("viewPos", movingCameraTransform.position);
	lightingShader.setFloat("material.shininess", 32.0f);
	//default value
	lightingShader.setVec4("color_mod", 1.0f,1.0f,1.0f, 1.0f);
	//fog parameters
	lightingShader.setFloat("fog_density", front::fogDensity);
	lightingShader.setVec4("fog_color", 0.7f*dayPart, 0.7f*dayPart, 0.7f*dayPart, 1.0f);

	//Setting lights
	// directional light
	lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	lightingShader.setVec3("dirLight.ambient", 0.03f+0.3f*dayPart, 0.03f+0.3f*dayPart, 0.03f+0.3f*dayPart);
	lightingShader.setVec3("dirLight.diffuse", 0.7f*dayPart, 0.7f*dayPart, 0.7f*dayPart);
	lightingShader.setVec3("dirLight.specular", 0.9f*dayPart, 0.9f*dayPart, 0.9f*dayPart);
	// point lights
	for(int i=0;i<NR_POINT_LIGHTS;i++) {
		lightingShader.setVec3("pointLights["+std::to_string(i)+"].position", front::pointLightPositions[i]);
		lightingShader.setVec3("pointLights["+std::to_string(i)+"].ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setVec3("pointLights["+std::to_string(i)+"].diffuse", 0.8f*(1.0f-dayPart), 0.8f*(1.0f-dayPart), 0.8f*(1.0f-dayPart));
		lightingShader.setVec3("pointLights["+std::to_string(i)+"].specular", 1.0f*(1.0f-dayPart), 1.0f*(1.0f-dayPart), 1.0f*(1.0f-dayPart));
		lightingShader.setFloat("pointLights["+std::to_string(i)+"].constant", 1.0);
		lightingShader.setFloat("pointLights["+std::to_string(i)+"].linear", 0.09);
		lightingShader.setFloat("pointLights["+std::to_string(i)+"].quadratic", 0.032);
	}
	// spotLight
	float tmp_angle2=glm::radians(spotLightAngle);
	for(int i=0;i<NR_SPOT_LIGHTS;i++) {
		lightingShader.setVec3("spotLights["+std::to_string(i)+"].position", glm::vec3({0.0f,1.7f,0.0f}));
		lightingShader.setVec3("spotLights["+std::to_string(i)+"].direction", glm::vec3(std::sin(tmp_angle2),0.0f,std::cos(tmp_angle2)));
		lightingShader.setVec3("spotLights["+std::to_string(i)+"].ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setVec3("spotLights["+std::to_string(i)+"].diffuse", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("spotLights["+std::to_string(i)+"].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("spotLights["+std::to_string(i)+"].constant", 1.0f);
		lightingShader.setFloat("spotLights["+std::to_string(i)+"].linear", 0.09);
		lightingShader.setFloat("spotLights["+std::to_string(i)+"].quadratic", 0.032);
		lightingShader.setFloat("spotLights["+std::to_string(i)+"].cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setFloat("spotLights["+std::to_string(i)+"].outerCutOff", glm::cos(glm::radians(15.0f)));
	}
	lightingShader.setVec4("color_mod", 1.0f,1.0f,1.0f, 1.0f);
	// render the loaded models
	//draw tiles
	for(int i=0;i<front::tiles.size();i++)
	{
		for(int j=0;j<front::tiles[i].size();j++)
		{
			front::Object object;
			if(front::tiles[i][j].type<0 || front::tiles[i][j].type>tileTypeModels.size())
				object = front::Object(tileTypeModels[0],glm::vec3((float)i,0.0f,(float)j));
			else
				object = front::Object(tileTypeModels[front::tiles[i][j].type],glm::vec3(i,front::tiles[i][j].level*0.5f,j));
			object.Draw(lightingShader);
		}
	}
	//draw units
	int ind=0;
	for(auto unit: front::units){
		float height=0.5f*(float)front::tiles[unit.x][unit.y].level;
		//last two parameters needed by that models
		front::Object object;
		if(ind!=front::focusedUnit)
			lightingShader.setVec4("color_mod", 0.7f,0.7f,0.7f, 1.0f);
		if(unit.type==0)
			object={unitTypeModels[unit.type],glm::vec3(unit.x,height,unit.y),glm::vec3(-90.0f,0.0f,180.0f),glm::vec3(0.01f,0.01f,0.01f)};
		else
			object={unitTypeModels[unit.type],glm::vec3(unit.x,height,unit.y),glm::vec3(-90.0f,0.0f,0.0f),glm::vec3(0.1f,0.1f,0.1f)};
		object.Draw(lightingShader);
		if(ind!=front::focusedUnit)
			lightingShader.setVec4("color_mod", 1.0f,1.0f,1.0f, 1.0f);
		ind++;
	}
	if(front::isGridOn)
		for (const auto & gridObject : front::gridObjects)
		{
			gridObject.Draw(lightingShader);
		}
	// render the loaded models
	//return to default value
	lightingShader.setVec4("color_mod", 1.0f,1.0f,1.0f, 1.0f);
	//return to default value
	lightingShader.setVec4("color_mod", 1.0f,1.0f,1.0f, 1.0f);

	// also draw the lamp object(s)
	lightCubeShader.use();
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);

	lightCubeShader.setFloat("fog_density", front::fogDensity);
	lightCubeShader.setVec4("fog_color", 0.5f, 0.5f, 0.5f, 1.0f);
	lightCubeShader.setVec3("camera_position", movingCameraTransform.position);

	//set night value
	lightCubeShader.setVec4("color", 1.0f,1.0f,1.0f,1.0f);
	// we now draw as many light bulbs as we have point lights.
	glBindVertexArray(front::lightCubeVAO);
	for (unsigned int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, front::pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		lightCubeShader.setMat4("model", model);
		glm::mat4 inv_model = glm::mat4(1.0f);
		inv_model = glm::inverse(model);
		inv_model = glm::transpose(inv_model);
		lightCubeShader.setMat4("ti_model", inv_model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

int main() {
	srand(time(0));
	 GameLogic logic;
	//getting map request
	 std::shared_ptr<MapResponse> response = std::static_pointer_cast<MapResponse>(logic.getInfo(std::make_shared<Request>("map")));
	 const std::vector<std::vector<Tile>>& map = response->getMap();
	 std::cout << "<Riku.cpp>" << map[0][0].biome.getName() << std::endl;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window= front::initWindow();
	//init shaders
	Shader lightingShader("../shaders/phong-vertex.shader","../shaders/phong-fragment.shader");

	Shader lightCubeShader("../shaders/light-vertex.shader","../shaders/light-fragment.shader");

	//load used models
	tileTypeModels.emplace_back("models/floor/water.obj",1,1);
	tileTypeModels.emplace_back("models/floor/grass.obj",1,1);
	tileTypeModels.emplace_back("models/floor/sand.obj",1,1);
	Model grid_model("models/floor/grid.obj",1,1);
	unitTypeModels.emplace_back("models/sara/model/sara.blend",1,-1);
	unitTypeModels.emplace_back("models/Assassin/Assassin.blend",1,-1);
	//vertices info (light cube)
	float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	//check Asset
	logic::AssetHandler handler;
	handler.findFiles("../assets");
	//as usual

	// create objects
	front::units.emplace_back(0,10,10);
	front::units.emplace_back(1,15,15);
	front::units.emplace_back(1,19,19);
	front::units.emplace_back(1,15,17);
	front::units.emplace_back(1,20,14);
	//object
	for(int i=0;i<40;i++) {
		std::vector<TileType> tmpTiles;
		for (int j = 0; j < 40; j++) {
			tmpTiles.emplace_back();
			tmpTiles.back().level=rand()%3;
			if(tmpTiles.back().level==0)
				tmpTiles.back().type=rand()%3;
			else
				tmpTiles.back().type=1+rand()%2;
		}
		front::tiles.push_back(tmpTiles);
	}

	// positions of the point lights
	front::pointLightPositions = {
			glm::vec3( 0.0f,  5.0f,  0.0f),
			glm::vec3( 0.0f,  5.0f,  20.0f),
			glm::vec3( 0.0f,  5.0f,  40.0f),
			glm::vec3( 20.0f,  5.0f,  0.0f),
			glm::vec3( 20.0f,  5.0f,  20.0f),
			glm::vec3( 20.0f,  5.0f,  40.0f),
			glm::vec3( 40.0f,  5.0f,  0.0f),
			glm::vec3( 40.0f,  5.0f,  20.0f),
			glm::vec3( 40.0f,  5.0f,  40.0f),
	};

	//vertex attributes
	// first, configure the cube's VAO (and VBO)
	unsigned int VBO/*, cubeVAO*/;
	//glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &front::lightCubeVAO);
	glBindVertexArray(front::lightCubeVAO);

	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// shader configuration
	// --------------------
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

	float lastFrame = 0.0f; // Time of last frame

	// Cegui config
	front::my_gui = CEGUI::GUI();
	front::my_gui.init("GUI");
	front::my_gui.loadScheme("TaharezLook.scheme");
	front::my_gui.loadScheme("AlfiskoSkin.scheme");
	front::my_gui.setFont("DejaVuSans-10");
	front::my_gui.loadLayout("application_templates.layout");
	//CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(front::my_gui.getWidgetByName("Button"));
	//testButton->setText("hell'o world");

	front::my_gui.setMouseCursor("TaharezLook/MouseArrow");
	front::my_gui.showMouseCursor();

	/*CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(front::my_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.5f, 0.5f, 0.1f, 0.05f), glm::vec4(0.0f), "TestButton"));
	testButton = static_cast<CEGUI::PushButton*>(front::my_gui.getWidgetByName("TestButton"));
	testButton->setText("Hello World!");*/

	//main loop
	while(!glfwWindowShouldClose(window))
	{
		//calculating deltaTime
		auto currentFrame = (float)glfwGetTime();
		front::deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//input
		processInput(window);
		// render
		// ------
		//day/night
		drawScene(lightingShader,lightCubeShader,currentFrame);
		front::my_gui.draw();
		//check and call events and swap the buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	//glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &front::lightCubeVAO);
	glDeleteBuffers(1, &VBO);
	//end of program
	glfwTerminate();
	return 0;
}

GLFWwindow* front::initWindow(){
	config.load();
	//set values
	movingCameraTransform=Transform(glm::vec3(20.0f, 20.0f, 20.0f),glm::vec3(glm::radians(config.angle),glm::radians(180.0f),0.0f));
	front::aspect=(float)config.screenWidth/config.screenHeight;
	GLFWwindow* window = glfwCreateWindow(config.screenWidth, config.screenHeight, "LearnOpenGL", config.isFullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (window == nullptr){
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	//glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_pos_callback);
	//glfwSetMouseButtonCallback(window, mouse_click_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	//GLEW: check errors
	GLenum err = glewInit();
	//myRenderer=std::make_unique(CEGUI::OpenGL3Renderer::create());
	//CEGUI::System::create( *myRenderer );
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	//std::cout << std::filesystem::current_path().string() << "\n";
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//system("pwd");
	return window;
}