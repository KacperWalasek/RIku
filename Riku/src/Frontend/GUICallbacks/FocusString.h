#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {       

    class FocusString : public Functor
    {
    private:
        std::string name;
        std::string& focusedString;
    public:
        FocusString(std::string name, std::string& focusedString)
            : Functor(), name(name), focusedString(focusedString) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            focusedString = name;
            return true;
        };
    };
}