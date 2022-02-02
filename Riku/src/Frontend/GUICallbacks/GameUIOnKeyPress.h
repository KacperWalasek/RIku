#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"
#include "EndTurn.h"
#include "PauseGame.h"

namespace CEGUI::Functor {

    class GameUIOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        CEGUI::GUI*& lastActiveGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        FrontendState& state;
        bool& isGameActive;
    public:
        GameUIOnKeyPress(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic, CEGUI::GUI*& lastActiveGUI, bool& isGameActive)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic), lastActiveGUI(lastActiveGUI), state(state), isGameActive(isGameActive) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
                case CEGUI::Key::Escape:
                {
                    CEGUI::Functor::PauseGame(isGameActive, true)(e);
                    auto f = CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic);
                    return f(e);
                }
                case CEGUI::Key::B:
                {
                    auto f = CEGUI::Functor::SwitchActiveGUI("BuildingUI", activeGUI, guiDic, false);
                    return f(e);
                }
                case CEGUI::Key::NumpadEnter:
                case CEGUI::Key::Return:
                {
                    
                    auto f = CEGUI::Functor::EndTurn(state, activeGUI, guiDic, lastActiveGUI);
                    return f(e);
                }
                default: break;
            }
            return false;
        };
    };
}