#pragma once

#include <CEGUI/CEGUI.h>
#include "GUI.h"
#include "FrontendState.h"

namespace CEGUI {
    class GUIUpdate {
    private:
        static int a;
        static std::map<std::string, CEGUI::Window*> existingUnitElems;
        static std::shared_ptr<std::string> activeUnitElem;
        static std::vector<std::shared_ptr<const Unit>> lastUnits;
        //static FrontendState* state;
        //static CEGUI::GUI** activeGUI;
        //static std::map<std::string, CEGUI::GUI*>* guiDic;
        //static int* focusedUnitIndex;
    public:
        ~GUIUpdate();
        //static void Init(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*>& guiDic, int& focusedUnitIndex);
        static void Init();
        static void UpdateResources(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic);
        static void UpdatePlayerChangedWindow(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic);
        static void CreateResources(CEGUI::GUI* my_gui, const CEGUI::String& resourcesListName, FrontendState& state);
        static void LoadIcons(FrontendState& state);
        static void CreateUnits(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex);
        static void CreateUnitOptions(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex);
    };
}