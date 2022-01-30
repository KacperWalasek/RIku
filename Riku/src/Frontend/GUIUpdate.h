#pragma once

#include <CEGUI/CEGUI.h>
#include "GUI.h"
#include "FrontendState.h"
#include "Transform.h"

namespace CEGUI {
    class GUIUpdate {
    private:
        static bool lastIsInMiniGame;
        static bool lastIsInGame;
        static int lastFocusedUnitIndex;
        static std::string lastFocusedSkill;
        static std::map<std::string, CEGUI::Window*> existingUnitElems;
        static std::map<std::string, CEGUI::Window*> existingMiniUnitElems;
        static std::map<std::string, CEGUI::Window*> existingSkillElems;
        static std::map<std::string, CEGUI::Window*> existingUnitOptions;
        static std::map<std::string, CEGUI::Window*> existingReceivedInvitations;
        static std::shared_ptr<std::string> activeUnitElem;
        static std::vector<std::shared_ptr<const Unit>> lastUnits;
        static std::vector<std::shared_ptr<const minigame::MiniUnit>> lastMiniUnits;
        static std::vector<std::string> lastSkills;
        static std::vector<std::string> unitNames;
        static std::vector<std::string> unitMiniNames;
        static std::vector<std::vector<std::string>> lastOptions;
        static std::vector<std::string> lastGUIHeaders;
        static std::map<std::string,std::string> lastBuildings;
        static std::map<std::string, Invitation> lastInvited;
        static std::map<std::string, std::string> lastReceivedInvitations;
    public:
        ~GUIUpdate();
        static void Init();
        static void UpdateResources(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic);
        static void UpdateMovementBars(FrontendState& state, std::map<std::string, CEGUI::GUI*> guiDic);
        static void CoreUpdate(FrontendState& state, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*> guiDic,
            int& focusedUnitIndex, std::string& focusedSkill, front::Transform& movingCameraTransform, CEGUI::GUI*& lastActiveGUI);
        static void UpdateUIButtons(std::map<std::string, CEGUI::GUI*> guiDic);
        static void CreateResources(CEGUI::GUI* my_gui, const CEGUI::String& resourcesListName, FrontendState& state);
        static void LoadIcons(FrontendState& state);
        static void CreateUnits(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex, front::Transform& movingCameraTransform);
        static void CreateSkills(CEGUI::GUI* my_gui, FrontendState& state, std::string& focusedSkill);
        static void CreateMiniUnits(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex, front::Transform& movingCameraTransform);
        static void CreateInvitations(CEGUI::GUI* my_gui, const CEGUI::String& InvitationsListName, FrontendState& state);
        static void CreateReceivedInvitations(CEGUI::GUI* my_gui, const CEGUI::String& InvitationsListName, FrontendState& state);
        static void CreateUnitOptions(CEGUI::GUI* my_gui, const CEGUI::String& unitsListName, FrontendState& state, int& focusedUnitIndex, std::map<std::string, CEGUI::GUI*> guiDic);
        static void CreateBuildingOptions(FrontendState& state, int& focusedUnitIndex, std::map<std::string, CEGUI::GUI*> guiDic);
        static void ShowPopup(std::string message, CEGUI::GUI*& activeGUI, std::map<std::string, CEGUI::GUI*> guiDic, CEGUI::GUI*& lastActiveGUI);
    };
}