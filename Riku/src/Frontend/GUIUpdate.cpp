#pragma once

#include "GUIUpdate.h"
#include "GUICallbacks/FocusUnitWithIndex.h"
#include "GUICallbacks/FocusUnit.h"
#include "GUICallbacks/SetLabelText.h"

int CEGUI::GUIUpdate::a;
std::map<std::string, CEGUI::Window*> CEGUI::GUIUpdate::existingUnitElems;
std::shared_ptr<std::string> CEGUI::GUIUpdate::activeUnitElem;
std::vector<std::shared_ptr<const Unit>> CEGUI::GUIUpdate::lastUnits;

//FrontendState* CEGUI::GUIUpdate::state;
//CEGUI::GUI** CEGUI::GUIUpdate::activeGUI;
//std::map<std::string, CEGUI::GUI*>* CEGUI::GUIUpdate::guiDic;
//int* CEGUI::GUIUpdate::focusedUnitIndex;
//
//void CEGUI::GUIUpdate::Init(FrontendState& estate, CEGUI::GUI*& eactiveGUI, std::map<std::string, CEGUI::GUI*>& eguiDic, int& efocusedUnitIndex)
//{
//    state = &estate;
//    activeGUI = &eactiveGUI;
//    guiDic = &eguiDic;
//    focusedUnitIndex = &efocusedUnitIndex;
//    a = 10;
//    activeUnitElem = std::make_shared<std::string>();
//}

void CEGUI::GUIUpdate::Init()
{
    a = 0;
    activeUnitElem = std::make_shared<std::string>();
}

CEGUI::GUIUpdate::~GUIUpdate()
{
    for (auto p : existingUnitElems)
        delete p.second;
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
            icon->setText(res.first + ": ");
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
    auto units = state.getUnits();
    for (auto u : units)
    {
        try
        {
            CEGUI::GUI::loadIcon(u.get()->getName(), u.get()->getName() + ".png"); //TODO wczytywanie ró¿nych formatów
            printf("Successfully loaded icon for: %s\n", u.get()->getName().c_str());
        }
        catch (...) {}
    }
}
void CEGUI::GUIUpdate::CreateUnits(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex)
{

    auto unitsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(unitsListName));
    auto player_units = state.getUnits();
    if (lastUnits.size() == player_units.size()) return;
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
            unitButton->setText(name);
        }
        else
        {
            unitButton->setProperty("HoverImage", unitName);
        }

        CEGUI::Window* movementBar = my_gui->createWidget("WindowsLook/Static",
            glm::vec4(0.85f, 0.1f, 0.1f, 0.8f), glm::vec4(0.0f), name + "/movement");
        movementBar->setProperty("BackgroundColours", "FF00FF00");
        movementBar->setProperty("FrameEnabled", "false");

        //CEGUI::Functor::FocusUnitWithIndex* func = new CEGUI::Functor::FocusUnitWithIndex(i, focusedUnitIndex, unitsList, name, activeUnitElem);
        CEGUI::Functor::FocusUnit* func = new CEGUI::Functor::FocusUnit(repeats[unitName], focusedUnitIndex, unitsList, unitName, activeUnitElem, state);
        my_gui->setPushButtonCallback(name + "/button", func);
        resourceElem->addChild(movementBar);
        resourceElem->addChild(unitButton);
        unitsList->addChild(resourceElem);

        existingUnitElems.insert(std::pair<std::string, CEGUI::Window*>(name, resourceElem));
        y += 0.35;
        i++;
    }
    lastUnits = player_units;
}

void CEGUI::GUIUpdate::CreateUnitOptions(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex)
{
    auto unitsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName("UnitsList"));
    auto nameLabel = static_cast<CEGUI::DefaultWindow*>(my_gui->getWidgetByName("NameLabel"));

    auto units = state.getUnits();
    if (focusedUnitIndex < 0 || focusedUnitIndex >= units.size()) return;

    auto unit = units[focusedUnitIndex].get();

    auto avaible_units = state.getGuiOptions(unit->getMapX(), unit->getMapY());

    CEGUI::PushButton* buildingButton;
    CEGUI::Functor::SetLabelText* func;
    float y = 0.1f;
    for (auto b : avaible_units)
    {
        try
        {
            auto win = unitsList->getChildRecursive(b);
            win->destroy();
        }
        catch (...) {}
        buildingButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
            glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), b));
        buildingButton->setText(b);
        func = new CEGUI::Functor::SetLabelText(b, nameLabel);
        my_gui->setPushButtonCallback(b, func);
        unitsList->addChild(buildingButton);
        y += 0.3;
    }

}
