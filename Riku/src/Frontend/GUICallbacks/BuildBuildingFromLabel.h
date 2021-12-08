#pragma once

#include <CEGUI/CEGUI.h>
#include "../FrontendState.h"
#include "Functor.h"

namespace CEGUI::Functor {

    class BuildBuildingFromLabel : public Functor
    {
    private:
        CEGUI::DefaultWindow* label;
        FrontendState& state;
        int& focusedUnitIndex;
    public:
        BuildBuildingFromLabel(CEGUI::DefaultWindow* label, FrontendState& state, int& focusedUnitIndex) 
            : Functor(), label(label), state(state), focusedUnitIndex(focusedUnitIndex) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto units = state.getUnits();
            if (focusedUnitIndex >= 0 && focusedUnitIndex < units.size())
            {
                auto unit = units[focusedUnitIndex].get();
                state.build(label->getText().c_str(), unit->getMapX(), unit->getMapY());
     /*           auto opt = state.getGuiOptions(unit->getMapX(), unit->getMapY());
                for (auto o : opt)
                {
                    printf("%s\n", o.c_str());
                }
                if (opt.empty())
                    state.build(label->getText().c_str(), unit->getMapX(), unit->getMapY());
                else
                    state.choseGuiOption(unit->getMapX(), unit->getMapY(), 0);*/
            }
            
            return true;
        };
    };
}