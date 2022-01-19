#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {
  
    class SetHotseatCountFromEditBox : public Functor
    {
    private:
        CEGUI::Editbox* nameBox;
        FrontendState& state;
    public:
        SetHotseatCountFromEditBox(CEGUI::Editbox* nameBox, FrontendState& state)
            : Functor(), nameBox(nameBox), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto s = nameBox->getText().c_str();
            int n = 1;
            try { n = std::stoi(s); }
            catch (...) {}
            state.setHotseatPlayerCount(n);
            return true;
        };
    };

}