#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {
  
    class StartGame : public Functor
    {
    private:
        FrontendState& state;
    public:
        StartGame(FrontendState& state)
            : Functor(), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.startGame();
            return true;
        };
    };

}