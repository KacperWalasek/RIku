#pragma once

#include <CEGUI/CEGUI.h>
#include "../FrontendState.h"
#include "Functor.h"
#include "BuildBuildingFromLabel.h"
#include "SwitchActiveGUI.h"

namespace CEGUI::Functor {

    class ConfirmBuilding : public Functor
    {
    private:
        CEGUI::DefaultWindow* label;
        FrontendState& state;
        int& focusedUnitIndex;
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
    public:
        ConfirmBuilding(CEGUI::DefaultWindow* label, FrontendState& state, int& focusedUnitIndex,
            CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic)
            : Functor(), label(label), state(state), focusedUnitIndex(focusedUnitIndex),
            activeGUI(activeGUI), guiDic(guiDic){}

        bool operator()(const CEGUI::EventArgs& e)
        {
            BuildBuildingFromLabel(label, state, focusedUnitIndex)(e);
            SwitchActiveGUI("GameUI", activeGUI, guiDic)(e);
            return true;
        };
    };
}