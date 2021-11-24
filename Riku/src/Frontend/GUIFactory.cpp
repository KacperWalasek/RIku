#include "GUIFactory.h"
#include <iostream>
#include <functional>

struct Unit1
{
	int type; //0 - Sara, 1 - assassin
	int x;
	int y;
	explicit Unit1(int type = 0, int x = 0, int y = 0) : type(type), x(x), y(y) {}
};

namespace front {
	extern int focusedUnit;
	extern CEGUI::GUI* activeGUI;
	extern std::vector<Unit1> units;
}

void CEGUI::GUIFactory::init(GLFWwindow* win){
    // init przyjmuje zmnienne, których mo¿emy potrzebowaæ dla funkcji callback
    window = win;
	auto v1 = CEGUI::GUI();
	v1.init();
	CEGUI::GUI::loadScheme("Generic.scheme");
	CEGUI::GUI::loadScheme("WindowsLook.scheme");
	CEGUI::GUI::loadScheme("TaharezLook.scheme");
	CEGUI::GUI::loadScheme("AlfiskoSkin.scheme");
	CEGUI::GUI::loadScheme("Riku.scheme");
	CEGUI::GUI::loadScheme("SampleBrowser.scheme");
	CEGUI::GUI::loadScheme("GameMenu.scheme");
	CEGUI::GUI::loadScheme("HUDDemo.scheme");
	CEGUI::GUI::loadScheme("OgreTray.scheme");
	CEGUI::GUI::loadScheme("VanillaSkin.scheme");
	CEGUI::GUI::loadScheme("VanillaCommonDialogs.scheme");	
}
CEGUI::GUIFactory::~GUIFactory()
{
	for(auto fun : callbacks)
		delete fun;
}

CEGUI::GUI* CEGUI::GUIFactory::GetDemoWindow() {
	
	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();	
	//my_gui->loadLayout("test.layout");


	my_gui->setFont("DejaVuSans-10");
	my_gui->loadLayout("application_templates.layout");

	auto OnExitButtonClicked1 = new CEGUI::Functor::ExitApp(my_gui, window);
	auto onF1 = new CEGUI::Functor::onKeyPress(my_gui);
	//std::function<bool(const CEGUI::EventArgs&)>* OnExitButtonClicked2 = new std::function<bool(const CEGUI::EventArgs&)>([=](const CEGUI::EventArgs& e)
	//{
	//	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(my_gui->getWidgetByName("Button"));
	//	testButton->setText("u sick ");
	//	//glfwSetWindowShouldClose(window, true);
	//	front::focusedUnit = 3;
	//	return true;
	//});

	callbacks.push_back(OnExitButtonClicked1);
	callbacks.push_back(onF1);
	my_gui->setPushButtonCallback("Button", OnExitButtonClicked1);
	my_gui->setKeyCallback(onF1);


	//my_gui->setMouseCursor("TaharezLook/MouseArrow");
	//my_gui->showMouseCursor();

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetMainMenu() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuMainMenu.layout");
	//my_gui->loadLayout("HUDDemoIngame.layout");
	my_gui->setFont("DejaVuSans-10");
	
	//auto img = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("StaticImage"));
	//img->setProperty("Image", "Riku/Background");

	auto onKeyPress = new CEGUI::Functor::MainMenuOnkeyPress(my_gui);
	auto onExitButton = new CEGUI::Functor::ExitApp(my_gui, window);
	callbacks.push_back(onKeyPress);
	callbacks.push_back(onExitButton);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ExitButton", onExitButton);


	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetGameUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	//my_gui->loadLayout("SampleBrowser.layout");
	my_gui->loadLayout("RikuGameUI.layout");
	//my_gui->setFont("DejaVuSans-10");

	auto unitsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName("UnitsList"));
	auto player_units = front::units; //logic.getInfo<UnitListResponse>("player_units");
	//CEGUI::PushButton* unit;
	int i = 1;
	float y = 0.1f;
	for (auto u : player_units)
	{
		CEGUI::PushButton* unit = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button", glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), "unit"+std::to_string(i)));
		unit->setText("unit"+std::to_string(i));
		unitsList->addChild(unit);
		i++;
		y += 0.3;
	}
	//CEGUI::PushButton* unit1 = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button", glm::vec4(0.4f, 0.5f, 0.5f, 1.5f), glm::vec4(0.0f), "unit1"));
	//CEGUI::PushButton* unit1 = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button", "unit1"));
	//unitsList->addChild(unit1);
	//auto list = static_cast<CEGUI::Listbox*>(my_gui->getWidgetByName("Listbox"));
	//Window* board = (my_gui->createWidget("OgreTray/ListboxItem", glm::vec4(0.5f, 0.5f, 1.1f, 1.05f), glm::vec4(0.0f), "item1"));
	//list->addChild(board);

	auto onKeyPress = new CEGUI::Functor::GameUIOnKeyPress(my_gui);
	callbacks.push_back(onKeyPress);
	my_gui->setKeyCallback(onKeyPress);

	return my_gui;
}