#pragma once

#include <CEGUI/CEGUI.h>
#include <GLFW/glfw3.h>
#include "Functor.h"
#include "../Config.h"
#include "../Lang.h"
#include "../GUIUpdate.h"

namespace CEGUI::Functor {

    class ApplySettings : public Functor
    {
    private:
        GLFWwindow* window;
        front::Config& config;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        CEGUI::Editbox* heightBox;
        CEGUI::Editbox* widthBox;
        CEGUI::ToggleButton* fullscreenBox;
    public:
        ApplySettings(GLFWwindow* window, front::Config& config, std::map<std::string, CEGUI::GUI*>& guiDic, CEGUI::Editbox* heightBox, CEGUI::Editbox* widthBox, CEGUI::ToggleButton* fullscreenBox)
            : Functor(), window(window), config(config), guiDic(guiDic), heightBox(heightBox), widthBox(widthBox), fullscreenBox(fullscreenBox){}

        bool operator()(const CEGUI::EventArgs& e) override
        {
            auto s = heightBox->getText().c_str();
            int height = 600;          
            try { height = std::stoi(s); }
            catch (...) {}
            s = widthBox->getText().c_str();
            int width = 800;
            try { width = std::stoi(s); }
            catch (...) {}
            config.screenHeight = height;
            config.screenWidth = width;
            config.isFullscreen = fullscreenBox->isSelected();
            config.save();

            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            int x = (mode->width - config.screenWidth) / 2;
            int y = (mode->height - config.screenHeight) / 2;

            glfwSetWindowMonitor(window, config.isFullscreen ? glfwGetPrimaryMonitor() : nullptr,
                x,
                y,
                config.screenWidth,
                config.screenHeight,
                GLFW_DONT_CARE
            );
            glfwSetWindowTitle(window, front::Lang::get("window_name"));
            CEGUI::GUIUpdate::UpdateSettingsDisplay(guiDic, config);
            return true;
        };
    };
}