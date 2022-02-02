#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"
#include "SaveGame.h"
#include "LoadGame.h"

namespace CEGUI::Functor {

    class LoadGamePopupOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        FrontendState& state;
        std::string& focusedSave;
    public:
        LoadGamePopupOnKeyPress(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic, std::string& focusedSave)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic), state(state), focusedSave(focusedSave) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
            case CEGUI::Key::Escape: return CEGUI::Functor::SwitchActiveGUI("NewGameMenu", activeGUI, guiDic, true)(e);
            case CEGUI::Key::NumpadEnter:
            case CEGUI::Key::Return:
            {
                CEGUI::Functor::SwitchActiveGUI("NewGameMenu", activeGUI, guiDic, true)(e);
                return CEGUI::Functor::LoadGame(state, focusedSave)(e);
            }
            default: break;
            }
            return true;
        };
    };
}