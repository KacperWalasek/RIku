#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {
  
    class SetLabelText : public Functor
    {
    private:
        std::string name;
        CEGUI::DefaultWindow* label;
    public:
        SetLabelText(std::string name, CEGUI::DefaultWindow* label) : Functor(), name(name), label(label) {}

        bool operator()([[maybe_unused]]const CEGUI::EventArgs& e)
        {
            label->setText((uint8*)name.c_str());
            return true;
        };
    };

}