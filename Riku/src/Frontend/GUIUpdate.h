#pragma once

#include <CEGUI/CEGUI.h>
#include "GUI.h"
#include "FrontendState.h"
#include "Transform.h"

namespace CEGUI {
    class GUIUpdate {
    private:
        static int a;
        static std::map<std::string, CEGUI::Window*> existingUnitElems;
        static std::map<std::string, CEGUI::Window*> existingUnitOptions;
        static std::shared_ptr<std::string> activeUnitElem;
        static std::vector<std::shared_ptr<const Unit>> lastUnits;
        static std::vector<std::vector<std::string>> lastOptions;
        static std::map<std::string,std::string> lastBuildings;
        static std::map<std::string, Invitation> lastInvited;
    public:
        ~GUIUpdate();
        static void Init();
        static void UpdateResources(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic);
        static void UpdateMovementBars(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic);
        static void CoreUpdate(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic, int& focusedUnitIndex, front::Transform& movingCameraTransform);
        static void UpdateUIButtons(std::map<std::string, CEGUI::GUI*> guiDic);
        static void UpdatePlayerChangedWindow(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic);
        static void CreateResources(CEGUI::GUI* my_gui, const CEGUI::String& resourcesListName, FrontendState& state);
        static void LoadIcons(FrontendState& state);
        static void CreateUnits(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex, front::Transform& movingCameraTransform);
        static void CreateInvitations(CEGUI::GUI* my_gui, const CEGUI::String& InvitationsListName, FrontendState& state);
        static void CreateUnitOptions(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex, std::map<std::string, CEGUI::GUI*> guiDic);
        static void CreateBuildingOptions(FrontendState& state, int& focusedUnitIndex, std::map<std::string, CEGUI::GUI*> guiDic);
    };
}