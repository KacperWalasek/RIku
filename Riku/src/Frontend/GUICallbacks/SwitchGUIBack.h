#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "Functor.h"

namespace CEGUI::Functor {

    class SwitchGUIBack : public Functor
    {
    private:
        CEGUI::GUI*& activeGUI;
        CEGUI::GUI*& lastActiveGUI;
        bool hideActive;
    public:
        SwitchGUIBack(CEGUI::GUI*& activeGUI, CEGUI::GUI*& lastActiveGUI)
            : Functor(), activeGUI(activeGUI), lastActiveGUI(lastActiveGUI) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            if (hideActive)
                activeGUI->hide();
            activeGUI = lastActiveGUI;
            activeGUI->show();
            return true;
        };
    };
}