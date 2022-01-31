#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {       

    class FocusSkill : public Functor
    {
    private:
        std::string name;
        std::string& focusedSkill;
        int skillNr;
        int& focusedSkillNr;
    public:
        FocusSkill(std::string name, std::string& focusedSkill, int skillNr, int& focusedSkillNr)
            : Functor(), name(name), focusedSkill(focusedSkill), skillNr(skillNr), focusedSkillNr(focusedSkillNr){}

        bool operator()(const CEGUI::EventArgs& e)
        {
            focusedSkill = name;
            focusedSkillNr = skillNr;
            return true;
        };
    };
}