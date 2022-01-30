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
#include "GUICallbacks/NewGameMenuOnkeyPress.h"
#include "GUICallbacks/InvitePlayerFromEditBox.h"
#include "GUICallbacks/StartGame.h"
#include "GUICallbacks/LoadGame.h"
#include "GUICallbacks/SaveGame.h"
#include "GUICallbacks/SetNameFromEditBox.h"
#include "GUICallbacks/SetHotseatCountFromEditBox.h"
#include "GUICallbacks/Resign.h"
#include "GUICallbacks/SwitchGUIBack.h"
#include "Lang.h"

CEGUI::GUIFactory::GUIFactory(GameLogic& logic, FrontendState& state, CEGUI::GUI*& activeGUI, CEGUI::GUI*& lastGUI,
	std::map<std::string, CEGUI::GUI*>& guiDic, int& focusedUnitIndex)
	:logic(logic), state(state), activeGUI(activeGUI), lastActiveGUI(lastGUI), guiDic(guiDic), focusedUnitIndex(focusedUnitIndex)
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
	auto onNewGameButton = new CEGUI::Functor::SwitchActiveGUI("NewGameMenu", activeGUI, guiDic);
	auto onJoinButton = new CEGUI::Functor::SwitchActiveGUI("JoinGameMenu", activeGUI, guiDic);
	auto onSaveButton = new CEGUI::Functor::SaveGame(state);

	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ExitButton", onExitButton);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);
	my_gui->setPushButtonCallback("OptionsButton", onOptionsButton);
	my_gui->setPushButtonCallback("NewGameButton", onNewGameButton);
	my_gui->setPushButtonCallback("JoinButton", onJoinButton);
	my_gui->setPushButtonCallback("SaveButton", onSaveButton);

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

	auto ipbox = static_cast<CEGUI::Editbox*>(my_gui->getWidgetByName("IpBox"));
	auto hotbox = static_cast<CEGUI::Editbox*>(my_gui->getWidgetByName("HotseatBox"));

	auto onKeyPress = new CEGUI::Functor::NewGameMenuOnkeyPress(activeGUI, guiDic);
	auto onReturnButton = new CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
	auto onInviteButton = new CEGUI::Functor::InvitePlayerFromEditBox(ipbox, state);
	auto onStartGameButton1 = new CEGUI::Functor::SetHotseatCountFromEditBox(hotbox, state);
	auto onStartGameButton2 = new CEGUI::Functor::StartGame(state);
	auto onLoadButton = new CEGUI::Functor::LoadGame(state);
	
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);
	my_gui->setPushButtonCallback("InviteButton", onInviteButton);
	my_gui->setPushButtonCallback("StartGameButton", onStartGameButton1);
	my_gui->setPushButtonCallback("StartGameButton", onStartGameButton2);
	my_gui->setPushButtonCallback("LoadButton", onLoadButton);

	//CEGUI::GUIUpdate::CreateInvitations(my_gui, "InvitationsList", state);
	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetJoinGameMenu() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuJoinGameMenu.layout");

	auto label = static_cast<CEGUI::Window*>(my_gui->getWidgetByName("IpLabel"));
	label->setText(front::Lang::getUtf("Your ip is"));
	label = static_cast<CEGUI::Window*>(my_gui->getWidgetByName("Ip"));
	label->setText(state.getIp());

	auto onKeyPress = new CEGUI::Functor::NewGameMenuOnkeyPress(activeGUI, guiDic); // to be changed
	auto onReturnButton = new CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
	my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ReturnButton", onReturnButton);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetGameUI() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuGameUI.layout");
	//CEGUI::GUIUpdate::CreateUnits(my_gui, "UnitsList", state, focusedUnitIndex);
	CEGUI::GUIUpdate::CreateResources(my_gui, "ResourcesList", state);

	auto onKeyPress = new CEGUI::Functor::GameUIOnKeyPress(state,activeGUI,guiDic, lastActiveGUI);
	auto onBuildingsButton = new CEGUI::Functor::SwitchActiveGUI("BuildingUI",activeGUI,guiDic,false);
	auto onRecruitingButton = new CEGUI::Functor::SwitchActiveGUI("RecruitingUI", activeGUI, guiDic, false);
	auto onEndTurnButton = new CEGUI::Functor::EndTurn(state, activeGUI, guiDic, lastActiveGUI);

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

CEGUI::GUI* CEGUI::GUIFactory::GetPopup() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuPopup.layout");

	auto onOkButton = new CEGUI::Functor::SwitchGUIBack(activeGUI, lastActiveGUI);
	auto onKeyPress = new CEGUI::Functor::Functor(); //do blokowania ruchu jednostk�
	my_gui->setPushButtonCallback("OkButton", onOkButton);
	my_gui->setKeyCallback(onKeyPress);

	return my_gui;
}

CEGUI::GUI* CEGUI::GUIFactory::GetSetNamePopup() {

	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuPopupWithEditbox.layout");

	auto label = static_cast<CEGUI::Window*>(my_gui->getWidgetByName("Label"));
	label->setText(front::Lang::getUtf("Please enter your name"));
	auto editbox = static_cast<CEGUI::Editbox*>(my_gui->getWidgetByName("Editbox"));
	auto onOkButton1 = new CEGUI::Functor::SetNameFromEditBox(editbox, state);
	auto onOkButton2 = new CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
	my_gui->setPushButtonCallback("OkButton", onOkButton1);
	my_gui->setPushButtonCallback("OkButton", onOkButton2);

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


CEGUI::GUI* CEGUI::GUIFactory::GetMiniGameUI() {
	CEGUI::GUI* my_gui = new CEGUI::GUI();
	my_gui->init();
	my_gui->loadLayout("RikuMiniGameUI.layout");

	//auto onKeyPress = new CEGUI::Functor::GameUIOnKeyPress(state, activeGUI, guiDic);
	auto onResignButton = new CEGUI::Functor::Resign(state);
	auto onEndTurnButton = new CEGUI::Functor::EndTurn(state, activeGUI, guiDic, lastActiveGUI);

	//my_gui->setKeyCallback(onKeyPress);
	my_gui->setPushButtonCallback("ResignButton", onResignButton);
	my_gui->setPushButtonCallback("EndTurnButton", onEndTurnButton);

	return my_gui;
}