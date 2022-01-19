#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {
  
    class AcceptInvitation : public Functor
    {
    private:
        std::string ip;
        FrontendState& state;
        CEGUI::Editbox* editBox; // hotseat count
    public:
        AcceptInvitation(CEGUI::Editbox* editBox, std::string ip, FrontendState& state)
            : Functor(), editBox(editBox), ip(ip), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto s = editBox->getText().c_str();
            int n = 1;
            try { n = std::stoi(s); }
            catch (...) {}
            state.acceptInvitation(ip, n);
            return true;
        };
    };

}