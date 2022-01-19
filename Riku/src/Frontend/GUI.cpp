#include "GUI.h"
#include "Lang.h"
#define RESPATH "../GUI"
//#include "../src/Riku.cpp"
CEGUI::OpenGL3Renderer* CEGUI::GUI::m_renderer = nullptr;
CEGUI::Key::Scan GlfwToCeguiKey(int glfwKey);

void CEGUI::GUI::init() {
    // Check if the renderer and system were not already initialized
    if (m_renderer == nullptr)
    {
        m_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
        CEGUI::GUI::setResourceDirectory(RESPATH);
    }
    
    m_context = &CEGUI::System::getSingleton().createGUIContext(m_renderer->getDefaultRenderTarget());
    m_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
    m_root->activate();
    m_root->setMousePassThroughEnabled(true);
    m_context->setRootWindow(m_root);
    setFontFromLang();
}

void CEGUI::GUI::setResourceDirectory(const CEGUI::String& resourceDirectory) {
    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
    rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
    rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
    rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
    rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
    rp->setResourceGroupDirectory("looknfeels", resourceDirectory + "/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");
    rp->setResourceGroupDirectory("icons", resourceDirectory + "/icons/");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
}

CEGUI::GUI::~GUI() {
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
    for (auto fun : callbacks)
        delete fun;
}

void CEGUI::GUI::draw(bool render) {
    if (!visible) return;
    if (render)
    {
        m_renderer->beginRendering();
        m_context->draw();
        m_renderer->endRendering();
        glDisable(GL_SCISSOR_TEST);
    }
    else m_context->draw();
}
void CEGUI::GUI::drawMultiple(std::map<std::string, CEGUI::GUI*>& guiDic) {
    m_renderer->beginRendering();
    for (auto p : guiDic)
        p.second->draw(false);
    m_renderer->endRendering();
    glDisable(GL_SCISSOR_TEST);
}
void CEGUI::GUI::show() {
    visible = true;
}
void CEGUI::GUI::hide() {
    visible = false;
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

bool CEGUI::GUI::on_key_press(int key){
    CEGUI::Key::Scan guiKey = GlfwToCeguiKey(key);
    auto b = m_context->injectKeyDown(guiKey);
    m_context->injectKeyUp(guiKey);
    if(!b)
        return m_context->injectChar(key);
    return b;
}

bool CEGUI::GUI::on_mouse_pos(float x, float y) {
    return m_context->injectMousePosition(x, y);
}

bool CEGUI::GUI::on_scroll(float delta)
{
    return m_context->injectMouseWheelChange(delta);
}

bool CEGUI::GUI::on_mouse_click(int button, int action) {
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
        return m_context->injectMouseButtonDown(guiButton);
    else if (action == GLFW_RELEASE)
        return m_context->injectMouseButtonUp(guiButton);
}

void CEGUI::GUI::setPushButtonCallback(const CEGUI::String& name, CEGUI::Functor::Functor* sub) {
    callbacks.push_back(sub);
    CEGUI::PushButton* button = static_cast<CEGUI::PushButton*>(getWidgetByName(name));
    button->subscribeEvent(CEGUI::PushButton::EventClicked, sub);
}
void CEGUI::GUI::setKeyCallback(CEGUI::Functor::Functor* sub) {
    callbacks.push_back(sub);
    m_root->subscribeEvent(CEGUI::Window::EventKeyDown, sub);
}

void CEGUI::GUI::loadScheme(const CEGUI::String& schemeFile) {
    CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

CEGUI::Window* CEGUI::GUI::loadLayout(const CEGUI::String& layoutFile) {
    CEGUI::Window* newWindow = WindowManager::getSingleton().loadLayoutFromFile(layoutFile);
    m_root->addChild(newWindow);
    return newWindow;
}

void CEGUI::GUI::loadIcon(const CEGUI::String& name, const CEGUI::String& path)
{
    CEGUI::ImageManager::getSingleton().addFromImageFile(name, path, "icons");
}

CEGUI::Window* CEGUI::GUI::createWidget(const CEGUI::String& type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const CEGUI::String& name /*= ""*/) {
    CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
    newWindow->setMouseInputPropagationEnabled(true);
    m_root->addChild(newWindow);
    setWidgetDestRect(newWindow, destRectPerc, destRectPix);
    return newWindow;
}

CEGUI::Window* CEGUI::GUI::createWidget(const CEGUI::String& type, const CEGUI::String& name) {
    CEGUI::Window* newWindow = CEGUI::WindowManager::getSingleton().createWindow(type, name);
    m_root->addChild(newWindow);
    return newWindow;
}

CEGUI::Window* CEGUI::GUI::getWidgetByName(const CEGUI::String& name){
    return m_root->getChildRecursive(name);
}

void CEGUI::GUI::setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix) {
    widget->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
    widget->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
}

void CEGUI::GUI::setFont(const CEGUI::String& fontFile) {
    CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
    m_context->setDefaultFont(fontFile);
}

bool CEGUI::GUI::setFontFromLang() {
    auto font = front::Lang::get("font");
    if (font == "font")
    {
        setFont("DejaVuSans-10");
        return false;
    }
    setFont(font);
    return true;
}

CEGUI::Key::Scan GlfwToCeguiKey(int glfwKey)
{
    switch (glfwKey)
    {
    case GLFW_KEY_UNKNOWN: return CEGUI::Key::Unknown;
    case GLFW_KEY_ESCAPE: return CEGUI::Key::Escape;
    case GLFW_KEY_0: return CEGUI::Key::Zero;
    case GLFW_KEY_PERIOD: return CEGUI::Key::Period;
    case GLFW_KEY_B: return CEGUI::Key::B;
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
    default: {
        if (glfwKey >= GLFW_KEY_1 && glfwKey <= GLFW_KEY_9)
            return (CEGUI::Key::Scan)(CEGUI::Key::One + glfwKey - GLFW_KEY_1);
        return CEGUI::Key::Unknown; 
        }
    }
}