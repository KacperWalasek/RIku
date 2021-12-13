#include "GUIFactory.h"
#include <iostream>
#include <functional>
#include "GUIUpdate.h"
#include "GUICallbacks/SwitchActiveGUI.h"
#include "GUICallbacks/EndTurn.h"
#include "GUICallbacks/ExitApp.h"
#include "GUICallbacks/BuildingUIOnKeyPress.h"
#include "GUICallbacks/RecruitingUIOnKeyPress.h"
#include "GUICallbacks/GameUIOnKeyPress.h"
#include "GUICallbacks/MainMenuOnkeyPress.h"
#include "GUICallbacks/SetLabelText.h" //to_delete
#include "Lang.h"

CEGUI::GUIFactory::GUIFactory(GameLogic& logic, FrontendState& state, CEGUI::GUI*& activeGUI,
	std::map<std::string, CEGUI::GUI*>& guiDic, int& focusedUnitIndex)
	:focusedUnitIndex(focusedUnitIndex), logic(logic), state(state), activeGUI(activeGUI), guiDic(guiDic)
{}

void CEGUI::GUIFactory::init(GLFWwindow* win){
    // init przyjmuje zmnienne, kt�rych mo�emy potrzebowa� dla funkcji callback
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
	CEGUI::GUIUpdate::Init();
	//CEGUI::GUIUpdate::Init(state, activeGUI, guiDic, focusedUnitIndex);
	CEGUI::GUIUpdate::LoadIcons(state);
}

CEGUI::GUI* CEGUI::GUIFactory::GetMainMenu() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuMainMenu.layout");
	
	//auto img = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("StaticImage"));
	//img->setProperty("Image", "Riku/Background");

	auto onKeyPress = new CEGUI::Functor::MainMenuOnkeyPress(activeGUI,guiDic);
	auto onExitButton = new CEGUI::Functor::ExitApp(window);
	auto onReturnButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
	auto onOptionsButton = new CEGUI::Functor::SwitchActiveGUI("OptionsMenu", activeGUI, guiDic);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ExitButton", onExitButton);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);
	my_gui->setPushButtonCallback("OptionsButton", onOptionsButton);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetOptionsMenu() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuOptionsMenu.layout");

	auto onKeyPress = new CEGUI::Functor::Functor();
	auto onReturnButton = new CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetGameUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuGameUI.layout");

	CEGUI::GUIUpdate::CreateUnits(my_gui, "UnitsList", state, focusedUnitIndex);
	CEGUI::GUIUpdate::CreateResources(my_gui, "ResourcesList", state);

	auto onKeyPress = new CEGUI::Functor::GameUIOnKeyPress(state,activeGUI,guiDic);
	auto onBuildingsButton = new CEGUI::Functor::SwitchActiveGUI("BuildingUI",activeGUI,guiDic,false);
	auto onRecruitingButton = new CEGUI::Functor::SwitchActiveGUI("RecruitingUI", activeGUI, guiDic, false);
	auto onEndTurnButton = new CEGUI::Functor::EndTurn(state, activeGUI, guiDic);

	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("BuildingsButton", onBuildingsButton);
	my_gui->setPushButtonCallback("RecruitingButton", onRecruitingButton);
	my_gui->setPushButtonCallback("EndTurnButton", onEndTurnButton);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetBuildingUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuBuildingUI.layout");

	auto buildingsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName("BuildingsList"));
	auto nameLabel = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("NameLabel"));
	auto frontNameLabel = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("FrontNameLabel"));
	auto avaible_buildings = state.getAvailableBuildings(0, 0); //TODO differ by unit position
	CEGUI::PushButton* buildingButton;
	CEGUI::Functor::SetLabelText* func;
	float y = 0.1f;
	//std::map<std::string, int> repeats;
	for (auto b : avaible_buildings)
	{
		buildingButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
			glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), b));
		buildingButton->setText(front::Lang::getUtf(b));
		func = new CEGUI::Functor::SetLabelText(b, nameLabel);
		my_gui->setPushButtonCallback(b, func);
		func = new CEGUI::Functor::SetLabelText(front::Lang::get(b), frontNameLabel);
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

	auto onOkButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
	auto onKeyPress = new CEGUI::Functor::Functor(); //do blokowania ruchu jednostk�
	my_gui->setPushButtonCallback("OkButton", onOkButton);
	my_gui->setKeyCallback(onKeyPress);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetRecruitingUI() {
	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuRecruitingUI.layout");

	auto nameLabel = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("NameLabel"));
	
	auto onKeyPress = new CEGUI::Functor::RecruitingUIOnKeyPress(activeGUI, guiDic, nameLabel, state, focusedUnitIndex);
	auto onConfirmButton = new CEGUI::Functor::RecruitUnit(nameLabel, state, focusedUnitIndex);
	auto onCloseButton = new CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);

	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("RecruitButton", onConfirmButton);
	my_gui->setPushButtonCallback("RecruitButton", onCloseButton);
	auto frameWindow = static_cast<CEGUI::FrameWindow*>(my_gui->getWidgetByName("RecruitingWindow"));
	frameWindow->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked, onCloseButton);

	return my_gui;
}