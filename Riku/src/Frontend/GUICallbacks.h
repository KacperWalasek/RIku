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
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
    public:
        SwitchActiveGUI(std::string guiName, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic) 
            : Functor(), guiName(guiName), activeGUI(activeGUI), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            activeGUI->hide();
            activeGUI = guiDic[guiName];
            activeGUI->show();
            return true;
        };
    };

    class EndTurn : public Functor
    {
        FrontendState& state;
        std::map<std::string, CEGUI::GUI*>& guiDic;
    public:
        EndTurn(FrontendState& state, std::map<std::string, CEGUI::GUI*>& guiDic) : Functor(), state(state), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.finishTurn();
            CEGUI::GUIUpdate::UpdateResources(state,guiDic);
            return true;
        };
    };

    class FocusUnitWithIndex : public Functor
    {
    private:
        int idx;
        const CEGUI::String& name;
        CEGUI::Window* unitsList;
        int& focusedUnitIndex;
    public:
        FocusUnitWithIndex(int idx, int& focusedUnitIndex, CEGUI::Window* unitsList, const CEGUI::String& name)
            : Functor(), idx(idx), focusedUnitIndex(focusedUnitIndex), unitsList(unitsList), name(name) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            focusedUnitIndex = idx;
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
        FrontendState& state;
        int& focusedUnitIndex;
    public:
        BuildBuildingFromLabel(CEGUI::DefaultWindow* label, FrontendState& state, int& focusedUnitIndex) 
            : Functor(), label(label), state(state), focusedUnitIndex(focusedUnitIndex) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto units = state.getUnits();
            if (focusedUnitIndex >= 0 && focusedUnitIndex < units.size())
            {
                auto unit = units[focusedUnitIndex].get();
                state.build(label->getText().c_str(), unit->getMapX(), unit->getMapY());
            }
            return true;
        };
    };

    class GameUIOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        FrontendState& state;
    public:
        GameUIOnKeyPress(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
                case CEGUI::Key::Escape:
                {
                    auto f = CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
                    return f(e);
                }
                case CEGUI::Key::B:
                {
                    auto f = CEGUI::Functor::SwitchActiveGUI("BuildingUI", activeGUI, guiDic);
                    return f(e);
                }
                case CEGUI::Key::NumpadEnter:
                case CEGUI::Key::Return:
                {
                    auto f = CEGUI::Functor::EndTurn(state, guiDic);
                    return f(e);
                }
                default: break;
            }

            return false;
        };
    };

    class MainMenuOnkeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
    public:
        MainMenuOnkeyPress(CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic) 
            : Functor(), activeGUI(activeGUI), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::Escape)
            {
                auto f = CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
                return f(e);
            }

            return false;
        };
    };

    class BuildingUIOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
    public:
        BuildingUIOnKeyPress(CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
            case CEGUI::Key::Escape:
            {
                auto f = CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
                return f(e);
            }
            case CEGUI::Key::B:
            {
                auto f = CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
                return f(e);
            }
            default: break;
            }

            return false;
        };
    };

}