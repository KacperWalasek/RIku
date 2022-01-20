#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {
  
    class SetNameFromEditBox : public Functor
    {
    private:
        CEGUI::Editbox* nameBox;
        FrontendState& state;
    public:
        SetNameFromEditBox(CEGUI::Editbox* nameBox, FrontendState& state)
            : Functor(), nameBox(nameBox), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.setName(nameBox->getText().c_str());
            return true;
        };
    };

}