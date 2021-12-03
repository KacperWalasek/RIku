#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"
#include "EndTurn.h"

namespace CEGUI::Functor {

    class GameUIOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        FrontendState& state;
    public:
        GameUIOnKeyPress(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
                case CEGUI::Key::Escape:
                {
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
                    auto f = CEGUI::Functor::EndTurn(state, activeGUI, guiDic);
                    return f(e);
                }
                default: break;
            }
            return false;
        };
    };
}