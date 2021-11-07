#include "GUIFactory.h"
#define RESPATH "GUI"
#include <iostream>
#include <functional>

namespace front {
	extern int focusedUnit;
}
bool OnExitButtonClicked(const CEGUI::EventArgs& e);

void CEGUI::GUIFactory::init(GLFWwindow* win){
    // init przyjmuje zmnienne, których mo¿emy potrzebowaæ dla funkcji callback
    window = win;
}

CEGUI::GUI* CEGUI::GUIFactory::GetDemoWindow() {
	
	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	if (resPath.empty())
	{
		resPath = RESPATH;
		CEGUI::GUI::setResourceDirectory(resPath);
		CEGUI::GUI::loadScheme("TaharezLook.scheme");
		CEGUI::GUI::loadScheme("AlfiskoSkin.scheme");
	}
	
	my_gui->setFont("DejaVuSans-10");
	my_gui->loadLayout("application_templates.layout");
	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(my_gui->getWidgetByName("Button"));
	testButton->setText("hell'o world");
	//testButton->subscribeEvent(CEGUI::PushButton::EventClicked, &OnButtonClicked);

	//CEGUI::GUI* shit = &my_gui;
	my_fun* OnExitButtonClicked1 = new my_fun(my_gui);
	std::function<bool(const CEGUI::EventArgs&)>* OnExitButtonClicked2 = new std::function<bool(const CEGUI::EventArgs&)>([=](const CEGUI::EventArgs& e)
	{
		//CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(shit->getWidgetByName("Button"));
		//testButton->setText("u sick pervert");
		//glfwSetWindowShouldClose(window, true);
		//CEGUI::GUI* win = &my_gui;
		//std::cout << "dgfgfg\n";
		//CEGUI::GUI* gui = shit;
		std::cout << "lambda dzia³a\n";
		CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(my_gui->getWidgetByName("Button"));
		return false;
	});
	my_gui->setButtonCallback("Button", OnExitButtonClicked1);
	my_gui->setButtonCallback("Button", OnExitButtonClicked2);

	my_gui->setMouseCursor("TaharezLook/MouseArrow");
	my_gui->showMouseCursor();

	return my_gui;
}