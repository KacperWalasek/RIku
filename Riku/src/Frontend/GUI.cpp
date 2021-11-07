#include "GUI.h"
//#include "../src/Riku.cpp"
CEGUI::OpenGL3Renderer* CEGUI::GUI::m_renderer = nullptr;
CEGUI::Key::Scan GlfwToCeguiKey(int glfwKey);

void CEGUI::GUI::init() {
    // Check if the renderer and system were not already initialized
    if (m_renderer == nullptr)
        m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
    
    m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
    m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
    m_context->setRootWindow(m_root);   
}

void CEGUI::GUI::setResourceDirectory(const CEGUI::String& resourceDirectory) {
    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
    rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
    rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
    rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
    rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
    rp->setResourceGroupDirectory("looknfeels", resourceDirectory + "/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
}

void CEGUI::GUI::destroy() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
}

void CEGUI::GUI::draw() {
    m_renderer->beginRendering();
    m_context->draw();
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}

void CEGUI::GUI::setMouseCursor(const CEGUI::String& imageFile) {
    m_context->getMouseCursor().setDefaultImage(imageFile);
}
void CEGUI::GUI::showMouseCursor() {
    m_context->getMouseCursor().show();
}
void CEGUI::GUI::hideMouseCursor() {
    m_context->getMouseCursor().hide();
}

void CEGUI::GUI::on_key_press(int key){
    //CEGUI::Key::Scan guiKey = GlfwToCeguiKey(key);
    switch (key)
    {
    case GLFW_KEY_F1: destroy();
        break;
    case GLFW_KEY_F2: 
        break;
    default:
        break;
    }
}

void CEGUI::GUI::on_mouse_pos(float x, float y) {
    m_context->injectMousePosition(x, y);
}

void CEGUI::GUI::on_mouse_click(int button, int action) {
    CEGUI::MouseButton guiButton = CEGUI::MouseButton::NoButton;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT: 
        guiButton = CEGUI::MouseButton::LeftButton;
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        guiButton = CEGUI::MouseButton::RightButton;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        guiButton = CEGUI::MouseButton::MiddleButton;
        break;
    default:
        break;
    }
    if (action == GLFW_PRESS)
        m_context->injectMouseButtonDown(guiButton);
    else if (action == GLFW_RELEASE)
        m_context->injectMouseButtonUp(guiButton);
}

void CEGUI::GUI::loadScheme(const CEGUI::String& schemeFile) {
    CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

CEGUI::Window* CEGUI::GUI::loadLayout(const CEGUI::String& layoutFile) {
    CEGUI::Window* newWindow = WindowManager::getSingleton().loadLayoutFromFile(layoutFile);
    m_root->addChild(newWindow);
    return newWindow;
}

CEGUI::Window* CEGUI::GUI::createWidget(const CEGUI::String& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const CEGUI::String& name /*= ""*/) {
    CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
    m_root->addChild(newWindow);
    setWidgetDestRect(newWindow, destRectPerc, destRectPix);
    return newWindow;
}

CEGUI::Window* CEGUI::GUI::getWidgetByName(const CEGUI::String& name){
    return m_root->getChildRecursive(name);
}

void CEGUI::GUI::setButtonCallback(const CEGUI::String& name, CEGUI::Event::Subscriber sub) {
    CEGUI::PushButton* button = static_cast<CEGUI::PushButton*>(getWidgetByName(name));
    button->subscribeEvent(CEGUI::PushButton::EventClicked, sub);
}

void CEGUI::GUI::setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix) {
    widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
    widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}

void CEGUI::GUI::setFont(const CEGUI::String& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context->setDefaultFont(fontFile);
}

CEGUI::Key::Scan GlfwToCeguiKey(int glfwKey)
{
    switch (glfwKey)
    {
    case GLFW_KEY_UNKNOWN: return CEGUI::Key::Unknown;
    case GLFW_KEY_ESCAPE: return CEGUI::Key::Escape;
    case GLFW_KEY_F1: return CEGUI::Key::F1;
    case GLFW_KEY_F2: return CEGUI::Key::F2;
    case GLFW_KEY_F3: return CEGUI::Key::F3;
    case GLFW_KEY_F4: return CEGUI::Key::F4;
    case GLFW_KEY_F5: return CEGUI::Key::F5;
    case GLFW_KEY_F6: return CEGUI::Key::F6;
    case GLFW_KEY_F7: return CEGUI::Key::F7;
    case GLFW_KEY_F8: return CEGUI::Key::F8;
    case GLFW_KEY_F9: return CEGUI::Key::F9;
    case GLFW_KEY_F10: return CEGUI::Key::F10;
    case GLFW_KEY_F11: return CEGUI::Key::F11;
    case GLFW_KEY_F12: return CEGUI::Key::F12;
    case GLFW_KEY_F13: return CEGUI::Key::F13;
    case GLFW_KEY_F14: return CEGUI::Key::F14;
    case GLFW_KEY_F15: return CEGUI::Key::F15;
    case GLFW_KEY_UP: return CEGUI::Key::ArrowUp;
    case GLFW_KEY_DOWN: return CEGUI::Key::ArrowDown;
    case GLFW_KEY_LEFT: return CEGUI::Key::ArrowLeft;
    case GLFW_KEY_RIGHT: return CEGUI::Key::ArrowRight;
    case GLFW_KEY_LEFT_SHIFT: return CEGUI::Key::LeftShift;
    case GLFW_KEY_RIGHT_SHIFT: return CEGUI::Key::RightShift;
    case GLFW_KEY_LEFT_CONTROL: return CEGUI::Key::LeftControl;
    case GLFW_KEY_RIGHT_CONTROL: return CEGUI::Key::RightControl;
    case GLFW_KEY_LEFT_ALT: return CEGUI::Key::LeftAlt;
    case GLFW_KEY_RIGHT_ALT: return CEGUI::Key::RightAlt;
    case GLFW_KEY_TAB: return CEGUI::Key::Tab;
    case GLFW_KEY_ENTER: return CEGUI::Key::Return;
    case GLFW_KEY_BACKSPACE: return CEGUI::Key::Backspace;
    case GLFW_KEY_INSERT: return CEGUI::Key::Insert;
    case GLFW_KEY_DELETE: return CEGUI::Key::Delete;
    case GLFW_KEY_PAGE_UP: return CEGUI::Key::PageUp;
    case GLFW_KEY_PAGE_DOWN: return CEGUI::Key::PageDown;
    case GLFW_KEY_HOME: return CEGUI::Key::Home;
    case GLFW_KEY_END: return CEGUI::Key::End;
    case GLFW_KEY_KP_ENTER: return CEGUI::Key::NumpadEnter;
    default: return CEGUI::Key::Unknown;
    }
}