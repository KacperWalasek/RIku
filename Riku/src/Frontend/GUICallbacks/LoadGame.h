#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {

    class LoadGame : public Functor
    {
    private:
        FrontendState& state;
    public:
        LoadGame(FrontendState& state)
            : Functor(), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.load("mySave");
            return true;
        };
    };

}