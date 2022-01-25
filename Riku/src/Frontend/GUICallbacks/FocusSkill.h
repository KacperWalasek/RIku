#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {       

    class FocusSkill : public Functor
    {
    private:
        std::string name;
        std::string& focusedSkill;
    public:
        FocusSkill(std::string name, std::string& focusedSkill)
            : Functor(), name(name), focusedSkill(focusedSkill) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            focusedSkill = name;
            return true;
        };
    };
}