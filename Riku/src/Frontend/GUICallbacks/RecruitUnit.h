#pragma once

#include <CEGUI/CEGUI.h>
#include "../FrontendState.h"
#include "Functor.h"

namespace CEGUI::Functor {

    class RecruitUnit : public Functor
    {
    private:
        CEGUI::DefaultWindow* label;
        FrontendState& state;
        int& focusedUnitIndex;
    public:
        RecruitUnit(CEGUI::DefaultWindow* label, FrontendState& state, int& focusedUnitIndex)
            : Functor(), label(label), state(state), focusedUnitIndex(focusedUnitIndex) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto units = state.getUnits();
            if (focusedUnitIndex >= 0 && focusedUnitIndex < units.size())
            {
                auto unit = units[focusedUnitIndex].get();
                auto option = label->getText();        
                auto options = state.getGuiOptions(unit->getMapX(), unit->getMapY());
                int i = 0;
                for (auto o : options)
                {
                    if (o == option)
                    {
                        printf("%s\n", o.c_str());
                        state.choseGuiOption(unit->getMapX(), unit->getMapY(), i); break;
                    }
                    i++;
                }
            }         
            return true;
        };
    };
}