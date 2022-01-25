#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {
  
    class Resign : public Functor
    {
    private:
        FrontendState& state;
    public:
        Resign(FrontendState& state)
            : Functor(), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.resign();
            return true;
        };
    };

}