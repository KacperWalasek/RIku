#pragma once

#include <CEGUI/CEGUI.h>
#include <GLFW/glfw3.h>
#include "Functor.h"

namespace CEGUI::Functor {

    class ExitApp : public Functor
    {
    private:
        GLFWwindow* window;
    public:
        ExitApp(GLFWwindow* window) : Functor(), window(window) {}

        bool operator()([[maybe_unused]]const CEGUI::EventArgs& e) override
        {
            glfwSetWindowShouldClose(window, true);
            return true;
        };
    };
}