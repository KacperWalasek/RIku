#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"

namespace CEGUI::Functor { 

    class NewGameMenuOnkeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
    public:
        NewGameMenuOnkeyPress(CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::Escape)
            {
                auto f = CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
                return f(e);
            }
            return false;
        };
    };
}