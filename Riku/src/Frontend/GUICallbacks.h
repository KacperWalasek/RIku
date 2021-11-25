#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>
#include "FrontendState.h"
#include "../GameLogic/GameLogic.h"
#include "GUIUpdate.h"

namespace front {
    extern int focusedUnit;
    extern CEGUI::GUI* activeGUI;
    extern std::map<std::string, CEGUI::GUI*> guiDic;
    extern int focusedUnitIndex;
    extern GameLogic logic;
    extern FrontendState state;
}

namespace CEGUI::Functor {

    class Functor
    {
    public:     
        Functor() {}
        virtual bool operator()(const CEGUI::EventArgs& e) { return true; }
        
    };

    class ExitApp : public Functor
    {
    private:
        GLFWwindow* window;
    public:
        ExitApp(GLFWwindow* window) : Functor(), window(window) {}

        bool operator()(const CEGUI::EventArgs& e) override
        {
            glfwSetWindowShouldClose(window, true);
            return true;
        };
    };

    class SwitchActiveGUI : public Functor
    {
    private:
        std::string guiName;
    public:
        SwitchActiveGUI(std::string guiName) : Functor(), guiName(guiName) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            front::activeGUI->hide();
            front::activeGUI = front::guiDic[guiName];
            front::activeGUI->show();
            return true;
        };
    };

    class FocusUnitWithIndex : public Functor
    {
    private:
        int idx;
        CEGUI::PushButton* button;
    public:
        FocusUnitWithIndex(int idx, CEGUI::PushButton* button) : Functor(), idx(idx), button(button) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            front::focusedUnitIndex = idx;
            //button->setProperty("NormalImage", "set:FTSUI image:full_image");
            return true;
        };
    };

    class SelectBuildingWithName : public Functor
    {
    private:
        std::string name;
        CEGUI::DefaultWindow* label;
    public:
        SelectBuildingWithName(std::string name, CEGUI::DefaultWindow* label) : Functor(), name(name), label(label) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            label->setText(name);
            return true;
        };
    };

    class BuildBuildingFromLabel : public Functor
    {
    private:
        CEGUI::DefaultWindow* label;
    public:
        BuildBuildingFromLabel(CEGUI::DefaultWindow* label) : Functor(), label(label) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto units = front::state.getUnits();
            if (front::focusedUnitIndex >= 0 && front::focusedUnitIndex < units.size())
            {
                auto unit = units[front::focusedUnitIndex].get();
                front::state.build(label->getText().c_str(), unit->getMapX(), unit->getMapY());
            }
            return true;
        };
    };

   /* class onKeyPress : public Functor
    {
    public:
        onKeyPress() : Functor() {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::F1)
                std::cout << "funktor dziala\n";
            
            return false;
        };
    };*/

    class GameUIOnKeyPress : public Functor
    {
    public:
        GameUIOnKeyPress() : Functor() {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
                case CEGUI::Key::Escape:
                {
                    auto f = CEGUI::Functor::SwitchActiveGUI("MainMenu");
                    return f(e);
                }
                case CEGUI::Key::B:
                {
                    auto f = CEGUI::Functor::SwitchActiveGUI("BuildingUI");
                    return f(e);
                }
                default: break;
            }

            return false;
        };
    };

    class MainMenuOnkeyPress : public Functor
    {
    public:
        MainMenuOnkeyPress() : Functor() {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::Escape)
            {
                auto f = CEGUI::Functor::SwitchActiveGUI("GameUI");
                return f(e);
            }

            return false;
        };
    };

    class BuildingUIOnKeyPress : public Functor
    {
    public:
        BuildingUIOnKeyPress() : Functor() {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
            case CEGUI::Key::Escape:
            {
                auto f = CEGUI::Functor::SwitchActiveGUI("GameUI");
                return f(e);
            }
            case CEGUI::Key::B:
            {
                auto f = CEGUI::Functor::SwitchActiveGUI("GameUI");
                return f(e);
            }
            default: break;
            }

            return false;
        };
    };

}