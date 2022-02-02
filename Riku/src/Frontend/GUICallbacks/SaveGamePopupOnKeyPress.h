#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"
#include "SaveGame.h"

namespace CEGUI::Functor {

    class SaveGamePopupOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        FrontendState& state;
        CEGUI::Editbox* nameBox;
    public:
        SaveGamePopupOnKeyPress(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic, CEGUI::Editbox* nameBox)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic), state(state), nameBox(nameBox) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
            case CEGUI::Key::Escape: return CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic, true)(e);
            case CEGUI::Key::NumpadEnter:
            case CEGUI::Key::Return:
            {
                CEGUI::Functor::SwitchActiveGUI("MainMenu", activeGUI, guiDic, true)(e);
                return CEGUI::Functor::SaveGame(nameBox, state)(e);
            }
            default: break;
            }
            return false;
        };
    };
}