#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <functional>

namespace CEGUI {
    class GUI {
    public:
        void init();
        //void destroy();
        void destroyWindowRecursive(CEGUI::Window& window);
        ~GUI();
        static void setResourceDirectory(const CEGUI::String& resourceDirectory);

        void draw();
        void show();
        void hide();

        void setMouseCursor(const CEGUI::String& imageFile);
        void showMouseCursor();
        void hideMouseCursor();

        //std::function<bool(int)>* on_key_press;
        bool on_key_press(int key);
        bool on_mouse_pos(float x, float y);
        bool on_mouse_click(int button, int action);

        static void loadScheme(const CEGUI::String& schemeFile);
        CEGUI::Window* loadLayout(const CEGUI::String& schemeFile);
        void setFont(const CEGUI::String& fontFile);
        CEGUI::Window* createWidget(const CEGUI::String& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const CEGUI::String& name = "");
        CEGUI::Window* createWidget(const CEGUI::String& type, const CEGUI::String& name = "");
        static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);
        CEGUI::Window* getWidgetByName(const CEGUI::String& name);
        void setPushButtonCallback(const CEGUI::String& name, CEGUI::Event::Subscriber sub);
        void setKeyCallback(CEGUI::Event::Subscriber sub);

        // Getters
        static CEGUI::OpenGL3Renderer* getRenderer() { return m_renderer; }
        const CEGUI::GUIContext* getContext() { return m_context; }
    private:
        static CEGUI::OpenGL3Renderer* m_renderer;
        CEGUI::GUIContext* m_context = nullptr;
        CEGUI::Window* m_root = nullptr;
        bool visible = false;
    };
}