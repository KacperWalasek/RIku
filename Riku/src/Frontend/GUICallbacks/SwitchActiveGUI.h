#pragma once

#include <CEGUI/CEGUI.h>
#include "../GUI.h"
#include "Functor.h"

namespace CEGUI::Functor {

    class SwitchActiveGUI : public Functor
    {
    private:
        std::string guiName;
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        bool hideActive;
    public:
        SwitchActiveGUI(std::string guiName, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic, bool hideActive = true) 
            : Functor(), guiName(guiName), activeGUI(activeGUI), guiDic(guiDic), hideActive(hideActive) {}

        bool operator()(const CEGUI::EventArgs&)
        {
            if (hideActive)
                activeGUI->hide();
            activeGUI = guiDic[guiName];
            activeGUI->show();
            return true;
        };
    };
}