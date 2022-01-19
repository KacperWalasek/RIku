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
    public:
        AcceptInvitation(std::string ip, FrontendState& state)
            : Functor(), ip(ip), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.acceptInvitation(ip, 2);
            return true;
        };
    };

}