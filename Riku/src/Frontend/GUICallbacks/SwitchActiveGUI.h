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
    public:
        SwitchActiveGUI(std::string guiName, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic) 
            : Functor(), guiName(guiName), activeGUI(activeGUI), guiDic(guiDic) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            activeGUI->hide();
            activeGUI = guiDic[guiName];
            activeGUI->show();
            return true;
        };
    };
}