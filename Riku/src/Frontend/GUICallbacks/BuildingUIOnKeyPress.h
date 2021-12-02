#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"

namespace CEGUI::Functor {

    class BuildingUIOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
    public:
        BuildingUIOnKeyPress(CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
                case CEGUI::Key::Escape:
                case CEGUI::Key::B:
                {
                    auto f = CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
                    return f(e);
                }
                case CEGUI::Key::Return:
                case CEGUI::Key::NumpadEnter:
                {
                    return true; // build with enter
                }
                default: break;
            }
            return false;
        };
    };
}