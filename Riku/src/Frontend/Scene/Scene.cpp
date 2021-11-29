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

front::Scene::Scene(Config& config, GameLogic& logic, FrontendState& state)
	: config(config), fac(logic,state,activeGUI, guiDic, focusedUnitIndex), logic(logic), state(state)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	initWindow();

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

front::Scene::~Scene()
{
	glfwTerminate();
}

bool front::Scene::update()
{
	if(glfwWindowShouldClose(window))
		return true;

	//calculating deltaTime
	auto currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	processInput();
	draw();
	for (auto p : guiDic)
	{
		p.second->draw(); // wyswietla tylko gui nawet jak nie sa poukrywane
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
	return false;
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

void front::Scene::processInput()
{//used for keys which are pressed continuously
	float rotSpeed = M_PI * deltaTime;
	float moveSpeed = 1.5f * std::sqrt(movingCameraTransform.position.y) * deltaTime;
	float scrollSpeed = 10.0f * deltaTime;
	float dx = 0.0f, dy = 0.0f;
	auto optCursorPos = getRelativeCursorPosition();
	//camera move
	if (optCursorPos.has_value()) {
		auto cursorPos = optCursorPos.value();
		if (cursorPos.x < 0.1f) {
			dx = 1.0f;
			dy = 1.0f - 2.0f * cursorPos.y;
		}
		else if (cursorPos.x > 0.9f) {
			dx = -1.0f;
			dy = 1.0f - 2.0f * cursorPos.y;
		}
		else if (cursorPos.y < 0.1f) {
			dy = 1.0f;
			dx = 1.0f - 2.0f * cursorPos.x;
		}
		else if (cursorPos.y > 0.9f) {
			dy = -1.0f;
			dx = 1.0f - 2.0f * cursorPos.x;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		dy++;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		dy--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		dx++;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		dx--;
	movingCameraTransform.position += front::rotate({ moveSpeed * dx,0.0f,moveSpeed * dy }, { 0.0f, movingCameraTransform.rotation.y, 0.0f });
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		movingCameraTransform.position.y -= moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		movingCameraTransform.position.y += moveSpeed;
	//process zoom
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		if (movingCameraTransform.position.y > config.minZoomHeight)
			movingCameraTransform.position += glm::rotateX(glm::vec3(0.f, -scrollSpeed, 0.f), (float)M_PI_4 - movingCameraTransform.rotation.x * .25f);
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		if (movingCameraTransform.position.y < config.maxZoomHeight)
			movingCameraTransform.position += glm::rotateX(glm::vec3(0.f, scrollSpeed, 0.f), (float)M_PI_4 - movingCameraTransform.rotation.x * .25f);
	if (movingCameraTransform.position.y < config.minZoomHeight)
		movingCameraTransform.position.y = config.minZoomHeight;
	if (movingCameraTransform.position.y > config.maxZoomHeight)
		movingCameraTransform.position.y = config.maxZoomHeight;
	//rotation
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		movingCameraTransform.rotation.y += rotSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		movingCameraTransform.rotation.y -= rotSpeed;
}

std::optional<glm::vec2> front::Scene::getRelativeCursorPosition()
{
	double x, y;
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &x, &y);
	x /= width;
	y /= height;
	if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
		return glm::vec2(x, y);
	return {};
}

void front::Scene::initWindow()
{
	config.load();
	//set values
	aspect = (float)config.screenWidth / config.screenHeight;
	window = glfwCreateWindow(config.screenWidth, config.screenHeight, "LearnOpenGL", config.isFullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	//glViewport(0, 0, 800, 600);
	setCallbacks();

	//GLEW: check errors
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void front::Scene::setCallbacks()
{
	
	glfwSetWindowUserPointer(window, this);

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
		ScrollCallback(scene->movingCameraTransform, scene->config)(window, xoffset, yoffset);
	});

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
		FramebufferSizeCallback(scene->aspect)(window, width, height);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
		MousePositionCallback(scene->activeGUI)(window, xpos, ypos);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
		MouseClickCallback(scene->activeGUI)(window, button, action, mods);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
		KeyCallback(scene->state, scene->focusedUnitIndex, scene->activeGUI)(window, key, scancode, action, mods);
	});
	
}
