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
	//TODO: make shders in initList !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	lightingShader.init("../shaders/phong-vertex.shader", "../shaders/phong-fragment.shader");
	lightCubeShader.init("../shaders/light-vertex.shader", "../shaders/light-fragment.shader");
	
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

	// positions of the point lights
	pointLightPositions = {
			glm::vec3(0.0f,  5.0f,  0.0f),
			glm::vec3(0.0f,  5.0f,  20.0f),
			glm::vec3(0.0f,  5.0f,  40.0f),
			glm::vec3(20.0f,  5.0f,  0.0f),
			glm::vec3(20.0f,  5.0f,  20.0f),
			glm::vec3(20.0f,  5.0f,  40.0f),
			glm::vec3(40.0f,  5.0f,  0.0f),
			glm::vec3(40.0f,  5.0f,  20.0f),
			glm::vec3(40.0f,  5.0f,  40.0f),
	};

	//set camera transform
	const auto& map = state.getMap();
	movingCameraTransform = Transform(glm::vec3(map.size() * 0.5f, 10.0f, map.size() * 0.5f), glm::vec3(glm::radians(config.angle), glm::radians(180.0f), 0.0f));

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);
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
	// directional light
	lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	lightingShader.setVec3("dirLight.ambient", 0.03f + 0.3f * dayPart, 0.03f + 0.3f * dayPart, 0.03f + 0.3f * dayPart);
	lightingShader.setVec3("dirLight.diffuse", 0.7f * dayPart, 0.7f * dayPart, 0.7f * dayPart);
	lightingShader.setVec3("dirLight.specular", 0.9f * dayPart, 0.9f * dayPart, 0.9f * dayPart);
	// point lights
	for (int i = 0; i < pointLightPositions.size(); i++) {
		lightingShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
		lightingShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", 0.8f * (1.0f - dayPart), 0.8f * (1.0f - dayPart), 0.8f * (1.0f - dayPart));
		lightingShader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f * (1.0f - dayPart), 1.0f * (1.0f - dayPart), 1.0f * (1.0f - dayPart));
		lightingShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
		lightingShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
		lightingShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032);
	}
	// spotLight
	float tmp_angle2 = glm::radians(spotLightAngle);
	for (int i = 0; i < NR_SPOT_LIGHTS; i++) {
		lightingShader.setVec3("spotLights[" + std::to_string(i) + "].position", glm::vec3({ 0.0f,1.7f,0.0f }));
		lightingShader.setVec3("spotLights[" + std::to_string(i) + "].direction", glm::vec3(std::sin(tmp_angle2), 0.0f, std::cos(tmp_angle2)));
		lightingShader.setVec3("spotLights[" + std::to_string(i) + "].ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setVec3("spotLights[" + std::to_string(i) + "].diffuse", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("spotLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("spotLights[" + std::to_string(i) + "].constant", 1.0f);
		lightingShader.setFloat("spotLights[" + std::to_string(i) + "].linear", 0.09);
		lightingShader.setFloat("spotLights[" + std::to_string(i) + "].quadratic", 0.032);
		lightingShader.setFloat("spotLights[" + std::to_string(i) + "].cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setFloat("spotLights[" + std::to_string(i) + "].outerCutOff", glm::cos(glm::radians(15.0f)));
	}
	lightingShader.setVec4("color_mod", 1.0f, 1.0f, 1.0f, 1.0f);
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

	// also draw the lamp object(s)
	lightCubeShader.use();
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);

	lightCubeShader.setFloat("fog_density", fogDensity);
	lightCubeShader.setVec4("fog_color", 0.5f, 0.5f, 0.5f, 1.0f);
	lightCubeShader.setVec3("camera_position", movingCameraTransform.position);

	//set night value
	lightCubeShader.setVec4("color", 1.0f, 1.0f, 1.0f, 1.0f);
	// we now draw as many light bulbs as we have point lights.
	glBindVertexArray(lightCubeVAO);
	for (unsigned int i = 0; i < pointLightPositions.size(); i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		lightCubeShader.setMat4("model", model);
		glm::mat4 inv_model = glm::mat4(1.0f);
		inv_model = glm::inverse(model);
		inv_model = glm::transpose(inv_model);
		lightCubeShader.setMat4("ti_model", inv_model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
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
