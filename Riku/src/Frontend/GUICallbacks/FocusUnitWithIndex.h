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
        std::vector<std::string> unitElems;
    public:
        FocusUnitWithIndex(int idx, int& focusedUnitIndex, CEGUI::Window* unitsList, std::string name, std::vector<std::string> unitElems)
            : Functor(), idx(idx), focusedUnitIndex(focusedUnitIndex), unitsList(unitsList), myName(name), unitElems(unitElems) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            focusedUnitIndex = idx;
            for (auto name : unitElems)
            {
                CEGUI::Window* child = unitsList->getChildRecursive(name);
                if (name == myName)
                    child->setProperty("BackgroundEnabled", "true");
                else child->setProperty("BackgroundEnabled", "false");
            }
            return true;
        };
    };
}