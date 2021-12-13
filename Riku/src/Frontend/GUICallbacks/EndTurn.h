#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "../FrontendState.h"
#include "../GUIUpdate.h"
#include "Functor.h"

namespace CEGUI::Functor {
 
    class EndTurn : public Functor
    {
        FrontendState& state;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        CEGUI::GUI*& activeGUI;
    public:
        EndTurn(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic)
            : Functor(), state(state), guiDic(guiDic), activeGUI(activeGUI) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.finishTurn();
            //CEGUI::GUIUpdate::UpdateResources(state, guiDic);
            printf("Turn of player %d\n", state.getPlayerOnMove());
            CEGUI::GUIUpdate::UpdatePlayerChangedWindow(state, guiDic);
            CEGUI::Functor::SwitchActiveGUI("PlayerChangedUI", activeGUI, guiDic, false)(e);
            return true;
        };
    };
}