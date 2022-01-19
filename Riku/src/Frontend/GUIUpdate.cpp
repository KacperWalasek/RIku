#pragma once

#include "Lang.h"
#include "GUIUpdate.h"
#include "GUICallbacks/FocusUnitWithIndex.h"
#include "GUICallbacks/FocusUnit.h"
#include "GUICallbacks/SetLabelText.h"
#include "GUICallbacks/AcceptInvitation.h"

int CEGUI::GUIUpdate::a;
std::map<std::string, CEGUI::Window*> CEGUI::GUIUpdate::existingUnitElems;
std::map<std::string, CEGUI::Window*> CEGUI::GUIUpdate::existingUnitOptions;
std::map<std::string, CEGUI::Window*> CEGUI::GUIUpdate::existingReceivedInvitations;
std::shared_ptr<std::string> CEGUI::GUIUpdate::activeUnitElem;
std::vector<std::shared_ptr<const Unit>> CEGUI::GUIUpdate::lastUnits;
std::vector<std::vector<std::string>> CEGUI::GUIUpdate::lastOptions;
std::map<std::string, std::string> CEGUI::GUIUpdate::lastBuildings;
std::map<std::string, Invitation> CEGUI::GUIUpdate::lastInvited;
std::map<std::string, std::string> CEGUI::GUIUpdate::lastReceivedInvitations;

void CEGUI::GUIUpdate::Init()
{
    a = 0;
    activeUnitElem = std::make_shared<std::string>();
}

CEGUI::GUIUpdate::~GUIUpdate()
{
    for (auto p : existingUnitElems)
        delete p.second;
    for (auto p : existingUnitOptions)
        delete p.second;
}

void CEGUI::GUIUpdate::CoreUpdate(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic, int& focusedUnitIndex, front::Transform& movingCameraTransform)
{
    if (state.isInGame())
    {
        CEGUI::GUIUpdate::CreateUnits(guiDic["GameUI"], "UnitsList", state, focusedUnitIndex, movingCameraTransform);
        CEGUI::GUIUpdate::CreateUnitOptions(guiDic["RecruitingUI"], "UnitsList", state, focusedUnitIndex, guiDic);
        CEGUI::GUIUpdate::CreateBuildingOptions(state, focusedUnitIndex, guiDic);
        CEGUI::GUIUpdate::UpdateResources(state, guiDic);
        CEGUI::GUIUpdate::UpdateMovementBars(state, guiDic);
    }
    else
    {
        CEGUI::GUIUpdate::CreateInvitations(guiDic["NewGameMenu"], "InvitationsList", state);
        CEGUI::GUIUpdate::CreateReceivedInvitations(guiDic["JoinGameMenu"], "InvitationsList", state);
    }
}

void CEGUI::GUIUpdate::UpdateMovementBars(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic)
{
    auto player_units = state.getUnits();
    std::map<std::string, int> repeats;
    for (auto u : player_units)
    {
        std::string unitName = u.get()->getName();
        if (repeats.find(unitName) == repeats.end())
            repeats.insert(std::pair<std::string, int>(unitName, 0));
        repeats[unitName]++;
        int count = repeats[unitName];
        std::string name = unitName + std::to_string(count);
        CEGUI::Window* movementBar = guiDic["GameUI"]->getWidgetByName(name + "/movement");
        CEGUI::Window* movementBarBG = guiDic["GameUI"]->getWidgetByName(name + "/movementBG");

        float mov = u.get()->movementPoints / (float)u.get()->baseMovementPoints;

        if (mov > 1)
        {
            mov -= 1;
            movementBar->setProperty("BackgroundColours", "FF8000FF");
            movementBarBG->setProperty("BackgroundColours", "FF00FF00");
        }
        else {
            movementBar->setProperty("BackgroundColours", "FF00FF00");
            movementBarBG->setProperty("BackgroundColours", "FFFF0000");
        }
        CEGUI::GUI::setWidgetDestRect(movementBar, glm::vec4(0.0f, 1.0f - mov, 1.0f, mov), glm::vec4(0.0f));
    }
}

void CEGUI::GUIUpdate::UpdateResources(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic)
{
    auto resources = state.getResources();
    CEGUI::Window* resourceElem;
    for (auto res : resources)
    {
        resourceElem = guiDic["GameUI"]->getWidgetByName(res.first + "/value");
        resourceElem->setText(std::to_string(res.second));
    }
}

void CEGUI::GUIUpdate::UpdateUIButtons(std::map<std::string, CEGUI::GUI*> guiDic)
{
    CEGUI::PushButton* button;

    button = static_cast<CEGUI::PushButton*>(guiDic["GameUI"]->getWidgetByName("BuildingsButton"));
    button->setText(front::Lang::getUtf("Buildings"));

    button = static_cast<CEGUI::PushButton*>(guiDic["GameUI"]->getWidgetByName("RecruitingButton"));
    button->setText(front::Lang::getUtf("Recruit units"));

    button = static_cast<CEGUI::PushButton*>(guiDic["GameUI"]->getWidgetByName("EndTurnButton"));
    button->setText(front::Lang::getUtf("End turn"));

    button = static_cast<CEGUI::PushButton*>(guiDic["MainMenu"]->getWidgetByName("ReturnButton"));
    button->setText(front::Lang::getUtf("Return to game"));

    button = static_cast<CEGUI::PushButton*>(guiDic["MainMenu"]->getWidgetByName("NewGameButton"));
    button->setText(front::Lang::getUtf("New Game"));

    button = static_cast<CEGUI::PushButton*>(guiDic["MainMenu"]->getWidgetByName("SaveButton"));
    button->setText(front::Lang::getUtf("Save Game"));

    button = static_cast<CEGUI::PushButton*>(guiDic["MainMenu"]->getWidgetByName("JoinButton"));
    button->setText(front::Lang::getUtf("Join Game"));

    button = static_cast<CEGUI::PushButton*>(guiDic["MainMenu"]->getWidgetByName("OptionsButton"));
    button->setText(front::Lang::getUtf("Options"));

    button = static_cast<CEGUI::PushButton*>(guiDic["MainMenu"]->getWidgetByName("ExitButton"));
    button->setText(front::Lang::getUtf("Exit"));
}

void CEGUI::GUIUpdate::UpdatePlayerChangedWindow(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic)
{
    auto label = guiDic["PlayerChangedUI"]->getWidgetByName("Label");
    label->setText("Turn of player " + std::to_string(state.getPlayerOnMove()));
}
void CEGUI::GUIUpdate::CreateResources(CEGUI::GUI* my_gui, const CEGUI::String& resourcesListName, FrontendState& state)
{
    auto resourcesList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(resourcesListName));
    if (my_gui == nullptr) return;
    auto resources = state.getResources();
    float x = 0.05f;
    CEGUI::Window* val;
    CEGUI::Window* resourceElem;
    for (auto res : resources)
    {
        CEGUI::Window* icon = my_gui->createWidget("WindowsLook/StaticImage", glm::vec4(0.1f, 0.0f, 0.4f, 1.0f), glm::vec4(0.0f), res.first + "/icon");
        icon->setProperty("Image", res.first);
        if (icon->getProperty("Image").empty())
        {
            icon->destroy();
            resourceElem = my_gui->createWidget("WindowsLook/Static", glm::vec4(x, 0.05f, 0.25f, 0.8f), glm::vec4(0.0f), res.first);
            icon = my_gui->createWidget("WindowsLook/Label", glm::vec4(0.05f, 0.1f, 0.6f, 0.8f), glm::vec4(0.0f), res.first + "/label");
            val = my_gui->createWidget("WindowsLook/Label", glm::vec4(0.65f, 0.1f, 0.35f, 0.8f), glm::vec4(0.0f), res.first + "/value");
            icon->setText(front::Lang::getUtf(res.first));
            x += 0.3;
        }
        else
        {
            icon->setTooltip(0);
            icon->setTooltipText(res.first); // niestety nie dziala
            resourceElem = my_gui->createWidget("WindowsLook/Static", glm::vec4(x, 0.05f, 0.15f, 0.8f), glm::vec4(0.0f), res.first);
            val = my_gui->createWidget("WindowsLook/Label", glm::vec4(0.55f, 0.1f, 0.4f, 0.8f), glm::vec4(0.0f), res.first + "/value");
            x += 0.2;
        }
        val->setText(std::to_string(res.second));
        resourceElem->addChild(icon);
        resourceElem->addChild(val);
        resourcesList->addChild(resourceElem);
    }
}
void CEGUI::GUIUpdate::LoadIcons(FrontendState& state)
{

    auto resources = state.getResources();
    for (auto res : resources)
    {
        try
        {
            CEGUI::GUI::loadIcon(res.first, res.first + ".png"); //TODO wczytywanie ró¿nych formatów
            printf("Successfully loaded icon for: %s\n", res.first.c_str());
        }
        catch (...) {}
    }
    auto units = state.getUnitNames();
    for (const std::string& u : units)
    {
        try
        {
            CEGUI::GUI::loadIcon(u, u + ".png"); //TODO wczytywanie ró¿nych formatów
            printf("Successfully loaded icon for: %s\n", u.c_str());
        }
        catch (...) {}
    }
}
void CEGUI::GUIUpdate::CreateUnits(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex, front::Transform& movingCameraTransform)
{
    auto unitsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(unitsListName));
    auto player_units = state.getUnits();
    if (lastUnits.size() == player_units.size()) return; // na razie zak³adam, ze jednostka nie moze po prostu zmieniæ sie w inn¹ jednostkê
    std::map<std::string, int> repeats;
    float y = 0.05f;
    int i = 0;
    for (auto p : existingUnitElems)
        unitsList->removeChild(p.second);
    for (auto u : player_units)
    {
        std::string unitName = u.get()->getName();
        if (repeats.find(unitName) == repeats.end())
            repeats.insert(std::pair<std::string, int>(unitName, 0));
        repeats[unitName]++;
        int count = repeats[unitName];
        std::string name = unitName + std::to_string(count);

        if (existingUnitElems.find(name) != existingUnitElems.end())
        {
            CEGUI::GUI::setWidgetDestRect(existingUnitElems[name], glm::vec4(0.1f, y, 0.8f, 0.30f), glm::vec4(0.0f));
            unitsList->addChild(existingUnitElems[name]);
            y += 0.35;
            i++;
            continue;
        }

        a++;
        printf("%d\n", a);

        CEGUI::Window* resourceElem = my_gui->createWidget("WindowsLook/Static",
            glm::vec4(0.1f, y, 0.8f, 0.30f), glm::vec4(0.0f), name);
        resourceElem->setProperty("BackgroundColours", "FF009999");
        if (focusedUnitIndex == i)
        {
            resourceElem->setProperty("BackgroundEnabled", "true");
            *activeUnitElem = name;
        }
        else resourceElem->setProperty("BackgroundEnabled", "false");

        CEGUI::PushButton* unitButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("Generic/ImageButton",
            glm::vec4(0.05f, 0.1f, 0.8f, 0.8f), glm::vec4(0.0f), name + "/button"));
        unitButton->setProperty("NormalImage", unitName);
        if (unitButton->getProperty("NormalImage").empty())
        {
            unitButton->destroy();
            unitButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
                glm::vec4(0.05f, 0.1f, 0.8f, 0.8f), glm::vec4(0.0f), name + "/button"));
            unitButton->setText(front::Lang::getUtf(unitName));
        }
        else
        {
            unitButton->setProperty("HoverImage", unitName);
        }
        CEGUI::Window* movementBarBG = my_gui->createWidget("WindowsLook/Static",
            glm::vec4(0.85f, 0.1f, 0.1f, 0.8f), glm::vec4(0.0f), name + "/movementBG");
        movementBarBG->setProperty("BackgroundColours", "FFFF0000");
        movementBarBG->setProperty("FrameEnabled", "false");

        CEGUI::Window* movementBar = my_gui->createWidget("WindowsLook/Static",
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f), name + "/movement");
        movementBar->setProperty("BackgroundColours", "FF00FF00");
        movementBar->setProperty("FrameEnabled", "false");

        //CEGUI::Functor::FocusUnitWithIndex* func = new CEGUI::Functor::FocusUnitWithIndex(i, focusedUnitIndex, unitsList, name, activeUnitElem);
        CEGUI::Functor::FocusUnit* func = new CEGUI::Functor::FocusUnit(repeats[unitName], focusedUnitIndex, unitsList, unitName, activeUnitElem, state, movingCameraTransform);
        my_gui->setPushButtonCallback(name + "/button", func);
        movementBarBG->addChild(movementBar);
        resourceElem->addChild(movementBarBG);
        resourceElem->addChild(unitButton);
        unitsList->addChild(resourceElem);

        existingUnitElems.insert(std::pair<std::string, CEGUI::Window*>(name, resourceElem));
        y += 0.35;
        i++;
    }
    lastUnits = player_units;
}

void CEGUI::GUIUpdate::CreateInvitations(CEGUI::GUI* my_gui, const CEGUI::String& InvitationsListName, FrontendState& state)
{
    std::map<std::string, Invitation> invited = state.getInvitedPlayers();
    //if (invited.size() == lastInvited.size())
        //return;

    auto invitationsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(InvitationsListName));

    for (const auto& invitation : lastInvited)
    {
        CEGUI::Window* item = static_cast<CEGUI::Window*>(invitationsList->getChildElementRecursive(invitation.first));
        invitationsList->removeChild(item);
        item->destroy();
        delete item;
    }
    float y = 0.1f;
    for (const auto& invitation : invited)
    {
        auto invitationLabel = static_cast<CEGUI::Window*>(my_gui->createWidget("WindowsLook/Label",
            glm::vec4(0.1f, y, 0.8f, 0.15f), glm::vec4(0.0f), invitation.first));
        //invitation inv = invitation.second;
        invitationLabel->setText(invitation.first + " - invitation state: " + invitation.second.GetStateAsString());
       /* auto callback1 = new CEGUI::Functor::SetLabelText(building.first, nameLabel);
        gui->setPushButtonCallback(building.first, callback1);
        auto callback2 = new CEGUI::Functor::SetLabelText(front::Lang::get(building.first), frontNameLabel);
        gui->setPushButtonCallback(building.first, callback2);*/
        invitationsList->addChild(invitationLabel);
        y += 0.2f;
    }
    lastInvited = invited;
}

void CEGUI::GUIUpdate::CreateReceivedInvitations(CEGUI::GUI* my_gui, const CEGUI::String& InvitationsListName, FrontendState& state)
{
    std::map<std::string, std::string> invitations = state.getInvitations();
    if (invitations == lastReceivedInvitations)
        return;

    auto invitationsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(InvitationsListName));

    for (auto p : existingReceivedInvitations)
        invitationsList->removeChild(p.second);
    
    float y = 0.1f;
    for (const auto& invitation : invitations)
    {
        auto ip = invitation.first;
        if (existingReceivedInvitations.find(ip) != existingReceivedInvitations.end())
        {
            CEGUI::GUI::setWidgetDestRect(existingReceivedInvitations[ip], glm::vec4(0.1f, y, 0.8f, 0.2f), glm::vec4(0.0f));
            invitationsList->addChild(existingReceivedInvitations[ip]);
            y += 0.2;
            continue;
        }
        auto item = my_gui->createWidget("DefaultWindow",
            glm::vec4(0.1f, y, 0.8f, 0.2f), glm::vec4(0.0f), ip);
        auto invitationLabel = static_cast<CEGUI::Window*>(my_gui->createWidget("WindowsLook/Label",
            glm::vec4(0.0f, 0.1f, 0.65f, 0.8f), glm::vec4(0.0f), ip +"/label"));
        auto button = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
            glm::vec4(0.65f, 0.1f, 0.35f, 0.8f), glm::vec4(0.0f), ip + "/button"));

        button->setText(front::Lang::getUtf("Accept"));
        std::string invitationFrom = front::Lang::get(std::string("Invitation from"));
        invitationFrom += ": ";
        if (invitation.second != "")
            invitationLabel->setText(invitationFrom + invitation.second);
        else
            invitationLabel->setText(invitationFrom + ip);
        auto callback1 = new CEGUI::Functor::AcceptInvitation(ip, state);
        my_gui->setPushButtonCallback(ip + "/button", callback1);
         /*auto callback2 = new CEGUI::Functor::SetLabelText(front::Lang::get(building.first), frontNameLabel);
         gui->setPushButtonCallback(building.first, callback2);*/
        item->addChild(invitationLabel);
        item->addChild(button);
        invitationsList->addChild(item);
        y += 0.2f;
        existingReceivedInvitations.insert(std::pair(ip, item));
    }
    lastReceivedInvitations = invitations;
}

void CEGUI::GUIUpdate::CreateUnitOptions(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex, std::map<std::string, CEGUI::GUI*> guiDic)
{
    auto units = state.getUnits();
    if (focusedUnitIndex < 0 || focusedUnitIndex >= units.size()) return;
    auto unit = units[focusedUnitIndex].get();
    auto avaible_options = state.getGuiOptions(unit->getMapX(), unit->getMapY());

    if (lastOptions.size() == avaible_options.size())
    {
        bool same = true;
        for (size_t i = 0; i < lastOptions.size(); i++)
            if (lastOptions[i] != avaible_options[i])
                same = false;
        if (same) return;
    }

    auto recruitButt = guiDic["GameUI"]->getWidgetByName("RecruitingButton");
    if (avaible_options.empty())
        recruitButt->setEnabled(false);
    else recruitButt->setEnabled(true);

    auto unitsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(unitsListName));
    for (auto p : existingUnitOptions)
        unitsList->removeChild(p.second);

    auto nameLabel = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("NameLabel"));
    auto frontNameLabel = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("FrontNameLabel"));
    CEGUI::PushButton* unitOptionButton;
    CEGUI::Functor::SetLabelText* func;
    float y = 0.1f;
    for (auto o : avaible_options)
    {
        std::string option = o[0];
        if (existingUnitOptions.find(option) != existingUnitOptions.end())
        {
            CEGUI::GUI::setWidgetDestRect(existingUnitOptions[option], glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f));
            unitsList->addChild(existingUnitOptions[option]);
            y += 0.3;
            continue;
        }
        unitOptionButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
            glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), option));
        unitOptionButton->setText(front::Lang::getUtf(option));
        func = new CEGUI::Functor::SetLabelText(option, nameLabel);
        my_gui->setPushButtonCallback(option, func);
        func = new CEGUI::Functor::SetLabelText(front::Lang::get(option), frontNameLabel);
        my_gui->setPushButtonCallback(option, func);
        unitsList->addChild(unitOptionButton);

        existingUnitOptions.insert(std::pair<std::string, CEGUI::Window*>(option, unitOptionButton));
        y += 0.3;
    }
    lastOptions = avaible_options;
}

void CEGUI::GUIUpdate::CreateBuildingOptions(FrontendState& state, int& focusedUnitIndex, std::map<std::string, CEGUI::GUI*> guiDic)
{
    auto units = state.getUnits();
    if (focusedUnitIndex < 0 || focusedUnitIndex >= units.size())
        return;
    auto unit = units[focusedUnitIndex];
    std::map<std::string, std::string> buildings = state.getAvailableBuildings(unit->getMapX(), unit->getMapY());

    if (buildings == lastBuildings)
        return;

    CEGUI::GUI* gui = guiDic["BuildingUI"];
    auto buildingList = static_cast<CEGUI::ScrollablePane*>(gui->getWidgetByName("BuildingsList"));
    auto nameLabel = static_cast<CEGUI::DefaultWindow*>(gui->getWidgetByName("NameLabel"));
    auto frontNameLabel = static_cast<CEGUI::DefaultWindow*>(gui->getWidgetByName("FrontNameLabel"));

    for (const auto& bulding : lastBuildings)
    {
        CEGUI::Window* item = static_cast<CEGUI::Window*>(buildingList->getChildElementRecursive(bulding.first));
        buildingList->removeChild(item);
        item->destroy();
        delete item;
    }
    float y = 0.1f;
    for (const auto& building : buildings)
    {
        auto buildingOptionButton = static_cast<CEGUI::PushButton*>(gui->createWidget("WindowsLook/Button",
            glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), building.first));
        buildingOptionButton->setText(front::Lang::getUtf(building.first));
        auto callback1 = new CEGUI::Functor::SetLabelText(building.first, nameLabel);
        gui->setPushButtonCallback(building.first, callback1);
        auto callback2 = new CEGUI::Functor::SetLabelText(front::Lang::get(building.first), frontNameLabel);
        gui->setPushButtonCallback(building.first, callback2);
        buildingList->addChild(buildingOptionButton);
        y += 0.3f;
    }
    lastBuildings = buildings;


}
