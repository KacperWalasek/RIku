#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>

namespace front {
    extern int focusedUnit;
    extern CEGUI::GUI* activeGUI;
    extern std::map<std::string, CEGUI::GUI*> guiDic;
}

namespace CEGUI::Functor {
   
    class Functor
    {
    protected:
        CEGUI::GUI* my_gui;
    public:     
        Functor(CEGUI::GUI* my_gui) : my_gui(my_gui) {}
        virtual bool operator()(const CEGUI::EventArgs& e) { return true; }
        
    };

    class ExitApp : public Functor
    {
    private:
        GLFWwindow* window;
    public:
        ExitApp(CEGUI::GUI* m_gui, GLFWwindow* window) : Functor(m_gui), window(window) {}

        bool operator()(const CEGUI::EventArgs& e) override
        {
            glfwSetWindowShouldClose(window, true);
            return true;
        };
    };

    class onKeyPress : public Functor
    {
    public:
        onKeyPress(CEGUI::GUI* m_gui) : Functor(m_gui) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::F1)
                std::cout << "funktor zajebisty\n";
            
            return false;
        };
    };

    class GameUIOnKeyPress : public Functor
    {
    public:
        GameUIOnKeyPress(CEGUI::GUI* m_gui) : Functor(m_gui) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::Escape)
            {        
                front::activeGUI->hide();
                front::activeGUI = front::guiDic["MainMenu"];
                front::activeGUI->show();
                return true;
            }

            return false;
        };
    };

    class MainMenuOnkeyPress : public Functor
    {
    public:
        MainMenuOnkeyPress(CEGUI::GUI* m_gui) : Functor(m_gui) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::Escape)
            {
                front::activeGUI->hide();
                front::activeGUI = front::guiDic["GameUI"];
                front::activeGUI->show();
                return true;
            }

            return false;
        };
    };
}