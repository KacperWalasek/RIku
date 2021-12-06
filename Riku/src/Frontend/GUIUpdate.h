#pragma once

#include <CEGUI/CEGUI.h>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include "GUICallbacks/FocusUnitWithIndex.h"

namespace CEGUI::GUIUpdate {
    static void UpdateResources(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic)
    {
        auto resources = state.getResources();
        CEGUI::Window* resourceElem;
        for (auto res : resources)
        {
            resourceElem = guiDic["GameUI"]->getWidgetByName(res.first + "/value");
            resourceElem->setText(std::to_string(res.second));
        }
    }
    static void UpdatePlayerChangedWindow(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic)
    {
        auto label = guiDic["PlayerChangedUI"]->getWidgetByName("Label");
        label->setText("Turn of player " + std::to_string(state.getPlayerOnMove()));
    }
    static void CreateResources(CEGUI::GUI* my_gui, const CEGUI::String& resourcesListName, FrontendState& state)
    {
        auto resourcesList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(resourcesListName));
        if (my_gui == nullptr) return;
        auto resources = state.getResources();
        float x = 0.05f;
        CEGUI::Window* val;
        CEGUI::Window* resourceElem;
        for (auto res : resources)
        {         
            CEGUI::Window* icon = my_gui->createWidget("WindowsLook/StaticImage", glm::vec4(0.1f, 0.0f, 0.4f, 1.0f), glm::vec4(0.0f), res.first+"/icon");
            icon->setProperty("Image", res.first);
            if (icon->getProperty("Image").empty())
            {
                icon->destroy();
                resourceElem = my_gui->createWidget("WindowsLook/Static", glm::vec4(x, 0.05f, 0.25f, 0.8f), glm::vec4(0.0f), res.first);
                icon = my_gui->createWidget("WindowsLook/Label", glm::vec4(0.05f, 0.1f, 0.6f, 0.8f), glm::vec4(0.0f), res.first + "/label");
                val = my_gui->createWidget("WindowsLook/Label", glm::vec4(0.65f, 0.1f, 0.35f, 0.8f), glm::vec4(0.0f), res.first + "/value");
                icon->setText(res.first+": ");
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
    static void LoadIcons(FrontendState& state)
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
    static void CreateUnits(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex)
    {
        auto unitsList = static_cast<CEGUI::ScrollablePane*>(my_gui->getWidgetByName(unitsListName));
        auto player_units = state.getUnits();
        float y = 0.05f;
        std::map<std::string, int> repeats;
        std::shared_ptr<std::string> activeUnitElem = std::make_shared<std::string>();
        int i = 0;
        for (auto u : player_units)
        {
            std::string name = u.get()->getName();
            if (repeats.find(name) == repeats.end())
                repeats.insert(std::pair<std::string, int>(name, 0));
            repeats[name]++;
            int count = repeats[name];
            name = name + std::to_string(count);

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
            unitButton->setProperty("NormalImage", u.get()->getName());
            if (unitButton->getProperty("NormalImage").empty())
            {
                unitButton->destroy();
                unitButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
                    glm::vec4(0.05f, 0.1f, 0.8f, 0.8f), glm::vec4(0.0f), name + "/button"));
                unitButton->setText(name);
            }
            else
            {
                unitButton->setProperty("HoverImage", u.get()->getName());         
            }

            CEGUI::Window* movementBar = my_gui->createWidget("WindowsLook/Static",
                glm::vec4(0.85f, 0.1f, 0.1f, 0.8f), glm::vec4(0.0f), name + "/movement");
            movementBar->setProperty("BackgroundColours", "FF00FF00");
            movementBar->setProperty("FrameEnabled", "false");

            CEGUI::Functor::FocusUnitWithIndex* func = new CEGUI::Functor::FocusUnitWithIndex(i, focusedUnitIndex, unitsList, name, activeUnitElem);
            //callbacks.push_back(func);
            my_gui->setPushButtonCallback(name + "/button", func);
            resourceElem->addChild(movementBar);
            resourceElem->addChild(unitButton);
            unitsList->addChild(resourceElem);
            y += 0.35;
            i++;
        }
    }
}