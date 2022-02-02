#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"
#include "PauseGame.h"

namespace CEGUI::Functor { 

    class MainMenuOnkeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        bool& isGameActive;
    public:
        MainMenuOnkeyPress(CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic, bool& isGameActive)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic), isGameActive(isGameActive) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            if (args.scancode == CEGUI::Key::Escape)
            {
                CEGUI::Functor::PauseGame(isGameActive, false)(e);
                auto f = CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
                return f(e);
            }
            return true;
        };
    };
}