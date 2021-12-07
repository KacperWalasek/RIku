#include "GUIFactory.h"
#include <iostream>
#include <functional>
#include "GUIUpdate.h"
#include "GUICallbacks/SwitchActiveGUI.h"
#include "GUICallbacks/EndTurn.h"
#include "GUICallbacks/ExitApp.h"
#include "GUICallbacks/ConfirmBuilding.h"
#include "GUICallbacks/BuildingUIOnKeyPress.h"
#include "GUICallbacks/GameUIOnKeyPress.h"
#include "GUICallbacks/MainMenuOnkeyPress.h"
#include "GUICallbacks/SelectBuildingWithName.h" //to_delete

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
	CEGUI::GUIUpdate::LoadIcons(state);
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

	//callbacks.push_back(OnExitButtonClicked1);
	my_gui->setPushButtonCallback("Button", OnExitButtonClicked1);


	//my_gui->setMouseCursor("TaharezLook/MouseArrow");
	//my_gui->showMouseCursor();

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetMainMenu() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuMainMenu.layout");
	my_gui->setFont("DejaVuSans-10");
	
	//auto img = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("StaticImage"));
	//img->setProperty("Image", "Riku/Background");

	auto onKeyPress = new CEGUI::Functor::MainMenuOnkeyPress(activeGUI,guiDic);
	auto onExitButton = new CEGUI::Functor::ExitApp(window);
	auto onReturnButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
	//callbacks.push_back(onKeyPress);
	//callbacks.push_back(onExitButton);
	//callbacks.push_back(onReturnButton);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ExitButton", onExitButton);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);


	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetGameUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuGameUI.layout");
	//my_gui->setFont("DejaVuSans-10");

	CEGUI::GUIUpdate::CreateUnits(my_gui, "UnitsList", state, focusedUnitIndex);
	CEGUI::GUIUpdate::CreateResources(my_gui, "ResourcesList", state);

	auto onKeyPress = new CEGUI::Functor::GameUIOnKeyPress(state,activeGUI,guiDic);
	auto onBuildingsButton = new CEGUI::Functor::SwitchActiveGUI("BuildingUI",activeGUI,guiDic,false);
	auto onEndTurnButton = new CEGUI::Functor::EndTurn(state, activeGUI, guiDic);
	//callbacks.push_back(onKeyPress);
	//callbacks.push_back(onBuildingsButton);
	//callbacks.push_back(onEndTurnButton);
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
	auto avaible_buildings = state.getAvailableBuildings(0, 0); //TODO differ by unit position
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
		//callbacks.push_back(func);
		my_gui->setPushButtonCallback(b, func);
		buildingsList->addChild(buildingButton);
		y += 0.3;
	}

	auto onKeyPress = new CEGUI::Functor::BuildingUIOnKeyPress(activeGUI, guiDic, nameLabel, state, focusedUnitIndex);
	//auto onConfirmButton = new CEGUI::Functor::ConfirmBuilding(nameLabel, state, focusedUnitIndex, activeGUI, guiDic);
	auto onConfirmButton = new CEGUI::Functor::BuildBuildingFromLabel(nameLabel, state, focusedUnitIndex);
	auto onCloseButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);

	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("BuildButton", onConfirmButton);
	my_gui->setPushButtonCallback("BuildButton", onCloseButton);
	auto frameWindow = static_cast<CEGUI::FrameWindow*>(my_gui->getWidgetByName("BuildingWindow"));
	frameWindow->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, onCloseButton);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetPlayerChangedUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuYourTurn.layout");
	my_gui->setFont("DejaVuSans-10");

	auto onOkButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
	auto onKeyPress = new CEGUI::Functor::Functor(); //do blokowania ruchu jednostk¹
	my_gui->setPushButtonCallback("OkButton", onOkButton);
	my_gui->setKeyCallback(onKeyPress);

	return my_gui;
}