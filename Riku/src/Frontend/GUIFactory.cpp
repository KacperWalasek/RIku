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
#include "GUICallbacks/NewGameMenuOnKeyPress.h"
#include "GUICallbacks/InvitePlayerFromEditBox.h"
#include "GUICallbacks/StartGame.h"
#include "Lang.h"

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
	auto onNewGameButton = new CEGUI::Functor::SwitchActiveGUI("NewGameMenu", activeGUI, guiDic);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ExitButton", onExitButton);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);
	my_gui->setPushButtonCallback("OptionsButton", onOptionsButton);
	my_gui->setPushButtonCallback("NewGameButton", onNewGameButton);

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

CEGUI::GUI* CEGUI::GUIFactory::GetNewGameMenu() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuNewGameMenu.layout");
	//my_gui->loadLayout("TextDemo.layout");

	auto box = static_cast<CEGUI::Editbox*>(my_gui->getWidgetByName("IpBox"));

	auto onKeyPress = new CEGUI::Functor::NewGameMenuOnkeyPress(activeGUI, guiDic);
	auto onReturnButton = new CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
	auto onInviteButton = new CEGUI::Functor::InvitePlayerFromEditBox(box, state);
	auto onStartGameButton = new CEGUI::Functor::StartGame(state);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);
	my_gui->setPushButtonCallback("InviteButton", onInviteButton);
	my_gui->setPushButtonCallback("StartGameButton", onStartGameButton);

	//CEGUI::GUIUpdate::CreateInvitations(my_gui, "InvitationsList", state);
	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetGameUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuGameUI.layout");
	//CEGUI::GUIUpdate::CreateUnits(my_gui, "UnitsList", state, focusedUnitIndex);
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
	auto onKeyPress = new CEGUI::Functor::Functor(); //do blokowania ruchu jednostk¹
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