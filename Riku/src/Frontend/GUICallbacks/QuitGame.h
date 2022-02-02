#pragma once

#include <CEGUI/CEGUI.h>
#include "../FrontendState.h"
#include "Functor.h"

namespace CEGUI::Functor {

    class QuitGame : public Functor
    {
    private:
        FrontendState& state;
    public:
        QuitGame(FrontendState& state) : Functor(), state(state) {}

        bool operator()(const CEGUI::EventArgs& e) override
        {
            state.quitGame();
            return true;
        };
    };
}