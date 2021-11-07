#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h";

namespace CEGUI {
    class GUIFactory {
    public:
        void init(GLFWwindow* win);
        CEGUI::GUI* GetDemoWindow();
        
    private:
        GLFWwindow* window;
        CEGUI::String resPath;
    };
}