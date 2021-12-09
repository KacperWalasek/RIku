#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
#include "../FrontendState.h"
#include "../Transform.h"
namespace CEGUI::Functor {       

    class FocusUnit : public Functor
    {
    private:
        int unitNr;
        std::string unitName;
        CEGUI::Window* unitsList;
        int& focusedUnitIndex;
        std::shared_ptr<std::string> activeUnitElem;
        FrontendState& state;
        front::Transform& movingCameraTransform;
    public:
        FocusUnit(int unitNr, int& focusedUnitIndex, CEGUI::Window* unitsList, std::string name, std::shared_ptr<std::string> activeUnitElem, FrontendState& state, front::Transform& movingCameraTransform)
            : Functor(), unitNr(unitNr), focusedUnitIndex(focusedUnitIndex), unitsList(unitsList), unitName(name), activeUnitElem(activeUnitElem), state(state), movingCameraTransform(movingCameraTransform) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            auto units = state.getUnits();
            int i = 0, num = 0;
            for (auto u : units)
            {
                if (u.get()->getName() == unitName)
                {
                    num++;
                    if (num == unitNr)
                    {
                        focusedUnitIndex = i;
                        CEGUI::Window* child = unitsList->getChildRecursive(*activeUnitElem.get());
                        if (child)
                            child->setProperty("BackgroundEnabled", "false");
                        std::string myName = unitName + std::to_string(unitNr);
                        CEGUI::Window* me = unitsList->getChildRecursive(myName);
                        me->setProperty("BackgroundEnabled", "true");
                        *activeUnitElem = myName;
                        auto pos = movingCameraTransform.position;
                        movingCameraTransform.position = glm::vec3(u.get()->getMapX(), pos.z, u.get()->getMapY());
                    }
                }
                i++;
            }          
            return true;
        };
    };
}