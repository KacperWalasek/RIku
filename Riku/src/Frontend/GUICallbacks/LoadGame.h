#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {

    class LoadGame : public Functor
    {
    private:
        FrontendState& state;
        std::string& focusedSave;
    public:
        LoadGame(FrontendState& state, std::string& focusedSave)
            : Functor(), state(state), focusedSave(focusedSave ){}

        bool operator()(const CEGUI::EventArgs& e)
        {
            std::string s = "../saves/" + focusedSave;
            state.load(s);
            return true;
        };
    };

}