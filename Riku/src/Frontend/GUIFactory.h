#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>
#include "GUICallbacks.h"

namespace CEGUI {
    class GUIFactory {
    public:
        int& focusedUnitIndex;

        GameLogic& logic;
        FrontendState& state;
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        GUIFactory(GameLogic& logic, FrontendState& state, CEGUI::GUI*& activeGUI,
            std::map<std::string, CEGUI::GUI*>& guiDic, int& focusedUnitIndex);
        void init(GLFWwindow* win);
        ~GUIFactory();
        CEGUI::GUI* GetDemoWindow();
        CEGUI::GUI* GetMainMenu();
        CEGUI::GUI* GetGameUI();
        CEGUI::GUI* GetBuildingUI();   

    private:
        GLFWwindow* window;
        CEGUI::String resPath;
        std::vector<CEGUI::Functor::Functor*> callbacks;
    };
    
}