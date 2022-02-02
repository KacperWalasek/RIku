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
        bool& isGameActive;

        GameLogic& logic;
        FrontendState& state;
        CEGUI::GUI*& activeGUI;
        CEGUI::GUI*& lastActiveGUI;
        std::map<std::string, CEGUI::GUI*>& guiDic;
        GUIFactory(GameLogic& logic, FrontendState& state, CEGUI::GUI*& activeGUI, CEGUI::GUI*& lastActiveGUI,
            std::map<std::string, CEGUI::GUI*>& guiDic, int& focusedUnitIndex, bool& isGameActive);
        void init(GLFWwindow* win);
        CEGUI::GUI* GetMainMenu();
        CEGUI::GUI* GetOptionsMenu();
        CEGUI::GUI* GetNewGameMenu();
        CEGUI::GUI* GetJoinGameMenu();
        CEGUI::GUI* GetGameUI();
        CEGUI::GUI* GetBuildingUI();
        CEGUI::GUI* GetRecruitingUI();
        CEGUI::GUI* GetPopup();
        CEGUI::GUI* GetSetNamePopup();
        CEGUI::GUI* GetSavePopup();
        CEGUI::GUI* GetMiniGameUI();
        CEGUI::GUI* GetLoadingScreen();
        CEGUI::GUI* GetLoadPopup();

    private:
        GLFWwindow* window;
        CEGUI::String resPath;
    };
    
}