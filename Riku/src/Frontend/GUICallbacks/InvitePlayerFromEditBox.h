#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {
  
    class InvitePlayerFromEditBox : public Functor
    {
    private:
        CEGUI::Editbox* ipBox;
        FrontendState& state;
    public:
        InvitePlayerFromEditBox(CEGUI::Editbox* ipBox, FrontendState& state) 
            : Functor(), ipBox(ipBox), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.invite(ipBox->getText().c_str());
            return true;
        };
    };

}