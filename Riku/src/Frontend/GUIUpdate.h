#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>
#include "GUICallbacks.h"

namespace CEGUI::GUIUpdate {
    static void UpdateResources(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic)
    {
        auto resources = state.getResources();
        CEGUI::PushButton* resButton;
        for (auto res : resources)
        {
            auto resButton = static_cast<CEGUI::PushButton*>(guiDic["GameUI"]->getWidgetByName(res.first));
            if (resButton != nullptr)
                resButton->setText(res.first + ": " + std::to_string(res.second));
        }
    }
    

}