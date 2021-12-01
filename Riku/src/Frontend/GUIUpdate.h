#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>
//#include "GUICallbacks.h"

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
    }
    static void CreateUnits(CEGUI::GUI* my_gui, CEGUI::Window* unitsList)
    {
        //auto player_units = front::state.getUnits(); //logic.getInfo<UnitListResponse>("player_units");
        //CEGUI::PushButton* unitButton;
        //CEGUI::Functor::FocusUnitWithIndex* func;
        //float y = 0.1f;
        //std::map<std::string, int> repeats;
        //int i = 0;
        //for (auto u : player_units)
        //{
        //    std::string name = u.get()->getName();
        //    if (repeats.find(name) == repeats.end())
        //        repeats.insert(std::pair<std::string, int>(name, 0));
        //    repeats[name]++;
        //    int count = repeats[name];
        //    unitButton = static_cast<CEGUI::PushButton*>(my_gui->createWidget("WindowsLook/Button",
        //        glm::vec4(0.1f, y, 0.8f, 0.25f), glm::vec4(0.0f), name + std::to_string(count)));
        //    unitButton->setText(name + std::to_string(count));
        //    func = new CEGUI::Functor::FocusUnitWithIndex(i, unitsList, name + std::to_string(count));
        //    //callbacks.push_back(func);
        //    my_gui->setPushButtonCallback(name + std::to_string(count), func);
        //    unitsList->addChild(unitButton);
        //    y += 0.3;
        //    i++;
        //}
    }
}