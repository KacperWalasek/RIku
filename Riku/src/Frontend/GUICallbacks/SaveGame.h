#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"

namespace CEGUI::Functor {

    class SaveGame : public Functor
    {
    private:
        CEGUI::Editbox* nameBox;
        FrontendState& state;
    public:
        SaveGame(CEGUI::Editbox* nameBox, FrontendState& state)
            : Functor(), nameBox(nameBox), state(state) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            //std::basic_string<unsigned char> text(reinterpret_cast<const unsigned char*>(nameBox->getText().c_str()));
            std::string s(nameBox->getText().c_str());
            s = "../saves/" + s + ".sav";
            state.save(s);
            return true;
        };
    };

}