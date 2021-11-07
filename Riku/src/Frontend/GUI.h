#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace CEGUI {
    class GUI {
    public:
        void init();
        void destroy();
        static void setResourceDirectory(const CEGUI::String& resourceDirectory);

        void draw();
        void setMouseCursor(const CEGUI::String& imageFile);
        void showMouseCursor();
        void hideMouseCursor();

        void on_key_press(int key);
        void on_mouse_pos(float x, float y);
        void on_mouse_click(int button, int action);

        static void loadScheme(const CEGUI::String& schemeFile);
        CEGUI::Window* loadLayout(const CEGUI::String& schemeFile);
        void setFont(const CEGUI::String& fontFile);
        CEGUI::Window* createWidget(const CEGUI::String& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const CEGUI::String& name = "");
        static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);
        CEGUI::Window* getWidgetByName(const CEGUI::String& name);
        void setButtonCallback(const CEGUI::String& name, CEGUI::Event::Subscriber sub);

        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
        const CEGUI::GUIContext* getContext() { return m_context; }
    public:
        static CEGUI::OpenGL3Renderer* m_renderer;
        CEGUI::GUIContext* m_context = nullptr;
        CEGUI::Window* m_root = nullptr;
    };
}