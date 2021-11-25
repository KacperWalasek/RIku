#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>
#include "GUICallbacks.h"

namespace front {
    extern int focusedUnit;
    extern CEGUI::GUI* activeGUI;
    extern std::map<std::string, CEGUI::GUI*> guiDic;
    extern int focusedUnitIndex;
    extern GameLogic logic;
    extern FrontendState state;
}

namespace CEGUI::GUIUpdate {
    static void UpdateResources()
    {
        auto resources = front::state.getResources();
        CEGUI::PushButton* resButton;
        for (auto res : resources)
        {
            auto resButton = static_cast<CEGUI::PushButton*>(front::guiDic["GameUI"]->getWidgetByName(res.first));
            if (resButton != nullptr)
                resButton->setText(res.first + ": " + std::to_string(res.second));
        }
    }
    

}