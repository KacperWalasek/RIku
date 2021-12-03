#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {
  
    class SelectBuildingWithName : public Functor
    {
    private:
        std::string name;
        CEGUI::DefaultWindow* label;
    public:
        SelectBuildingWithName(std::string name, CEGUI::DefaultWindow* label) : Functor(), name(name), label(label) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            label->setText(name);
            return true;
        };
    };

}