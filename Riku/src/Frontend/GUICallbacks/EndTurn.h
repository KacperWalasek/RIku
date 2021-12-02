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
    public:
        EndTurn(FrontendState& state, std::map<std::string, CEGUI::GUI*>& guiDic) : Functor(), state(state), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.finishTurn();
            CEGUI::GUIUpdate::UpdateResources(state, guiDic);
            return true;
        };
    };
}