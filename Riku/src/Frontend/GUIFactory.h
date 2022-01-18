#pragma once

#include <CEGUI/CEGUI.h>
#include "GUI.h"
#include "GUICallbacks/Functor.h"
#include "FrontendState.h"
#include "../GameLogic/GameLogic.h"

namespace CEGUI {
    class GUIFactory {
    public:
        int& focusedUnitIndex;

        GameLogic& logic;
        FrontendState& state;
        CEGUI::GUI*& activeGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        GUIFactory(GameLogic& logic, FrontendState& state, CEGUI::GUI*& activeGUI,
            std::map<std::string, CEGUI::GUI*>& guiDic, int& focusedUnitIndex);
        void init(GLFWwindow* win);
        CEGUI::GUI* GetMainMenu();
        CEGUI::GUI* GetOptionsMenu();
        CEGUI::GUI* GetNewGameMenu();
        CEGUI::GUI* GetGameUI();
        CEGUI::GUI* GetBuildingUI();
        CEGUI::GUI* GetRecruitingUI();
        CEGUI::GUI* GetPlayerChangedUI();

    private:
        GLFWwindow* window;
        CEGUI::String resPath;
    };
    
}