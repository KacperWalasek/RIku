#pragma once
#define _USE_MATH_DEFINES

struct GLFWwindow;
namespace CEGUI {
	class GUI;
}

namespace front {
	class Scene;
	class MouseClickCallback
	{
		CEGUI::GUI* activeGUI;
		Scene* scene;
		void MiniGameLeftClick(int px, int py);
		void GameLeftClick(int px, int py);
	public:
		MouseClickCallback(CEGUI::GUI* activeGUI, Scene* scene) : activeGUI(activeGUI), scene(scene) {}

		void operator()(GLFWwindow* window, int button, int action, int mods);
	};
}

