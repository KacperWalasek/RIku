#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>

namespace CEGUI {
    class GUIFactory {
    public:
        void init(GLFWwindow* win);
        CEGUI::GUI* GetDemoWindow();
        
    private:
        GLFWwindow* window;
        CEGUI::String resPath;
    };
    
    class my_fun
    {
    public:
        CEGUI::GUI* my_gui;
        my_fun(CEGUI::GUI* my_gui): my_gui(my_gui){}

        bool operator()(const CEGUI::EventArgs& e)
        {
            //CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(shit->getWidgetByName("Button"));
            //testButton->setText("u sick pervert");
            //glfwSetWindowShouldClose(window, true);
            //CEGUI::GUI* win = &my_gui;
            //std::cout << "dgfgfg\n";
            //CEGUI::GUI* gui = shit;
            std::cout << "funktor dzia³a\n";
            CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(my_gui->getWidgetByName("Button"));
            return false;
        };

    };
}