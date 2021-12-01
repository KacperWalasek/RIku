#include "GUIFactory.h"
#include <iostream>
#include <functional>
#include "FrontendState.h"
#include "../GameLogic/GameLogic.h"

CEGUI::GUIFactory::GUIFactory(GameLogic& logic, FrontendState& state, CEGUI::GUI*& activeGUI,
	std::map<std::string, CEGUI::GUI*>& guiDic, int& focusedUnitIndex)
	:logic(logic), state(state), activeGUI(activeGUI), guiDic(guiDic), focusedUnitIndex(focusedUnitIndex)
{}

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

	auto OnExitButtonClicked1 = new CEGUI::Functor::ExitApp(window);
	//std::function<bool(const CEGUI::EventArgs&)>* OnExitButtonClicked2 = new std::function<bool(const CEGUI::EventArgs&)>([=](const CEGUI::EventArgs& e)
	//{
	//	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(my_gui->getWidgetByName("Button"));
	//	testButton->setText("u sick ");
	//	//glfwSetWindowShouldClose(window, true);
	//	front::focusedUnit = 3;
	//	return true;
	//});

	callbacks.push_back(OnExitButtonClicked1);
	my_gui->setPushButtonCallback("Button", OnExitButtonClicked1);


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

	auto onKeyPress = new CEGUI::Functor::MainMenuOnkeyPress(activeGUI,guiDic);
	auto onExitButton = new CEGUI::Functor::ExitApp(window);
	auto onReturnButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
	callbacks.push_back(onKeyPress);
	callbacks.push_back(onExitButton);
	callbacks.push_back(onReturnButton);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ExitButton", onExitButton);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);


	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetGameUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	//my_gui->loadLayout("SampleBrowser.layout");
	my_gui->loadLayout("RikuGameUI.layout");
	//my_gui->setFont("DejaVuSans-10");

	auto unitsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName("UnitsList"));
	auto player_units = state.getUnits(); //logic.getInfo<UnitListResponse>("player_units");
	CEGUI::PushButton* unitButton;
	CEGUI::Functor::FocusUnitWithIndex* func;
	float y = 0.1f;
	std::map<std::string, int> repeats;
	int i = 0;
	for (auto u : player_units)
	{
		std::string name = u.get()->getName();
		if (repeats.find(name) == repeats.end())
			repeats.insert(std::pair<std::string, int>(name, 0));
		repeats[name]++;
		int count = repeats[name];
		unitButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
			glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), name + std::to_string(count)));
		unitButton->setText(name + std::to_string(count));
		func = new CEGUI::Functor::FocusUnitWithIndex(i, unitButton, focusedUnitIndex);
		callbacks.push_back(func);
		my_gui->setPushButtonCallback(name + std::to_string(count), func);
		unitsList->addChild(unitButton);
		y += 0.3;
		i++;
	}

	auto resourcesList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName("ResourcesList"));
	auto resources = state.getResources();
	CEGUI::PushButton* resButton;
	//CEGUI::DefaultWindow* label;
	float x = 0.05f;
	for (auto res : resources)
	{		
		resButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
			glm::vec4(x, 0.1f, 0.15f, 0.8f), glm::vec4(0.0f), res.first));
		resButton->setText(res.first + ": " + std::to_string(res.second));
		//resButton->disable();
		//label = static_cast<CEGUI::DefaultWindow*>(my_gui->createWidget("WindowsLook/Label",
			//glm::vec4(x, 0.1f, 0.15f, 0.8f), glm::vec4(0.0f), res.first + "Label"));
		//label->setAlwaysOnTop(true);
		resourcesList->addChild(resButton);
		//resourcesList->addChild(label);
		x += 0.2;
	}
	//auto list = static_cast<CEGUI::Listbox*>(my_gui->getWidgetByName("Listbox"));
	//Window* board = (my_gui->createWidget("OgreTray/ListboxItem", glm::vec4(0.5f, 0.5f, 1.1f, 1.05f), glm::vec4(0.0f), "item1"));
	//list->addChild(board);

	auto onKeyPress = new CEGUI::Functor::GameUIOnKeyPress(state,activeGUI,guiDic);
	auto onBuildingsButton = new CEGUI::Functor::SwitchActiveGUI("BuildingUI",activeGUI,guiDic);
	auto onEndTurnButton = new CEGUI::Functor::EndTurn(state, guiDic);
	callbacks.push_back(onKeyPress);
	callbacks.push_back(onBuildingsButton);
	callbacks.push_back(onEndTurnButton);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("BuildingsButton", onBuildingsButton);
	my_gui->setPushButtonCallback("EndTurnButton", onEndTurnButton);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetBuildingUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuBuildingUI.layout");

	auto buildingsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName("BuildingsList"));
	auto nameLabel = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("NameLabel"));
	auto avaible_buildings = state.getAvailableBuildings(0, 0);
	CEGUI::PushButton* buildingButton;
	CEGUI::Functor::SelectBuildingWithName* func;
	float y = 0.1f;
	//std::map<std::string, int> repeats;
	for (auto b : avaible_buildings)
	{
		buildingButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
			glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), b));
		buildingButton->setText(b);
		func = new CEGUI::Functor::SelectBuildingWithName(b, nameLabel);
		callbacks.push_back(func);
		my_gui->setPushButtonCallback(b, func);
		buildingsList->addChild(buildingButton);
		y += 0.3;
	}

	auto onKeyPress = new CEGUI::Functor::BuildingUIOnKeyPress(activeGUI, guiDic);
	auto onConfirmButton = new CEGUI::Functor::BuildBuildingFromLabel(nameLabel, state, focusedUnitIndex);
	auto onCloseButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
	callbacks.push_back(onKeyPress);
	callbacks.push_back(onConfirmButton);
	callbacks.push_back(onCloseButton);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("BuildButton", onConfirmButton);
	auto frameWindow = static_cast<CEGUI::FrameWindow*>(my_gui->getWidgetByName("BuildingWindow"));
	frameWindow->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, onCloseButton);

	return my_gui;
}

//void CEGUI::GUIFactory::UpdateResources()
//{
//	auto resources = front::state.getResources();
//	CEGUI::PushButton* resButton;
//	for (auto res : resources)
//	{
//		auto resButton = static_cast<CEGUI::PushButton*>(front::guiDic["GameUI"]->getWidgetByName(res.first));
//		if (resButton != nullptr)
//			resButton->setText(res.first + ": " + std::to_string(res.second));
//	}
//}