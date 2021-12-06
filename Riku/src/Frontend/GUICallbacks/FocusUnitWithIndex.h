#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {       

    class FocusUnitWithIndex : public Functor
    {
    private:
        int idx;
        std::string myName;
        CEGUI::Window* unitsList;
        int& focusedUnitIndex;
        std::shared_ptr<std::string> activeUnitElem;
    public:
        FocusUnitWithIndex(int idx, int& focusedUnitIndex, CEGUI::Window* unitsList, std::string name, std::shared_ptr<std::string> activeUnitElem)
            : Functor(), idx(idx), focusedUnitIndex(focusedUnitIndex), unitsList(unitsList), myName(name), activeUnitElem(activeUnitElem) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            focusedUnitIndex = idx;
            CEGUI::Window* child = unitsList->getChildRecursive(*activeUnitElem.get());
            if (child)
                child->setProperty("BackgroundEnabled", "false");
            CEGUI::Window* me = unitsList->getChildRecursive(myName);
            me->setProperty("BackgroundEnabled", "true");
            //activeUnitElem.reset(new std::string(myName));
            *activeUnitElem = myName;
            return true;
        };
    };
}