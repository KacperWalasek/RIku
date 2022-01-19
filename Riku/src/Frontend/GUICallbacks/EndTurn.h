#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "../GUIUpdate.h"
#include "Functor.h"
#include "../Lang.h"

namespace CEGUI::Functor {
 
    class EndTurn : public Functor
    {
        FrontendState& state;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        CEGUI::GUI*& activeGUI;
        CEGUI::GUI*& lastActiveGUI;
    public:
        EndTurn(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic, CEGUI::GUI*& lastActiveGUI)
            : Functor(), state(state), activeGUI(activeGUI), guiDic(guiDic), lastActiveGUI(lastActiveGUI){}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.finishTurn();
            std::string s = front::Lang::get("Turn of player");
            s += ": ";
            s += std::to_string(state.getPlayerOnMove());
            printf("%s", s.c_str());
            CEGUI::GUIUpdate::ShowPopup(s, activeGUI, guiDic, lastActiveGUI);
            //CEGUI::Functor::SwitchActiveGUI("PlayerChangedUI", activeGUI, guiDic, false)(e);
            return true;
        };
    };
}