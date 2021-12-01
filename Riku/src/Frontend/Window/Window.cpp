#define _USE_MATH_DEFINES 
#include <iostream>
#include "Window.h"
#include "Callbacks/ScrollCallback.h"
#include "Callbacks/FramebufferSizeCallback.h"
#include "Callbacks/MousePositionCallback.h"
#include "Callbacks/MouseClickCallback.h"
#include "Callbacks/KeyCallback.h"

front::Window::Window(Config& config, GameLogic& logic, FrontendState& state, const AssetHandler& handler)
	: config(config), scene(config, logic, state, handler, aspect)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	initWindow();
	scene.init(window);
}

front::Window::~Window()
{
	glfwTerminate();
}

bool front::Window::update()
{
	if (glfwWindowShouldClose(window))
		return true;

	auto currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	processInput();
	scene.update();

	glfwSwapBuffers(window);
	glfwPollEvents();
	return false;
}

void front::Window::initWindow()
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

void front::Window::setCallbacks()
{
	glfwSetWindowUserPointer(window, &scene);

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
		MouseClickCallback(scene->activeGUI, scene)(window, button, action, mods);
		});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
		KeyCallback(scene->state, scene->focusedUnitIndex, scene->activeGUI, scene->config, scene->movingCameraTransform)(window, key, scancode, action, mods);
		});

}

void front::Window::processInput()
{//used for keys which are pressed continuously
	Transform& movingCameraTransform = scene.movingCameraTransform;
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

std::optional<glm::vec2> front::Window::getRelativeCursorPosition()
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