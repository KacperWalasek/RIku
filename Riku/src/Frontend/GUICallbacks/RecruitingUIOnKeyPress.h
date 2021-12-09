#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "Functor.h"
#include "SwitchActiveGUI.h"
#include "RecruitUnit.h"

namespace CEGUI::Functor {

    class RecruitingUIOnKeyPress : public Functor
    {
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        CEGUI::DefaultWindow* label;
        FrontendState& state;
        int& focusedUnitIndex;
    public:
        RecruitingUIOnKeyPress(CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic,
            CEGUI::DefaultWindow* label, FrontendState& state, int& focusedUnitIndex)
            : Functor(), activeGUI(activeGUI), guiDic(guiDic),
            label(label), state(state), focusedUnitIndex(focusedUnitIndex) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto args = static_cast<const CEGUI::KeyEventArgs&>(e);
            switch (args.scancode)
            {
                case CEGUI::Key::Escape:
                {
                    auto f = CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic);
                    return f(e);
                }
                case CEGUI::Key::Return:
                case CEGUI::Key::NumpadEnter:
                {
                    auto f = CEGUI::Functor::RecruitUnit(label, state, focusedUnitIndex);
                    CEGUI::Functor::SwitchActiveGUI("GameUI", activeGUI, guiDic)(e);
                    return f(e);
                }
                default: break;
            }
            return false;
        };
    };
}