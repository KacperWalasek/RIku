#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {

    class SaveGame : public Functor
    {
    private:
        FrontendState& state;
    public:
        SaveGame(FrontendState& state)
            : Functor(), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            state.save("mySave");
            return true;
        };
    };

}