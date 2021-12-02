#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"

namespace CEGUI::Functor {       

    class FocusUnitWithIndex : public Functor
    {
    private:
        int idx;
        const CEGUI::String& name;
        CEGUI::Window* unitsList;
        int& focusedUnitIndex;
    public:
        FocusUnitWithIndex(int idx, int& focusedUnitIndex, CEGUI::Window* unitsList, const CEGUI::String& name)
            : Functor(), idx(idx), focusedUnitIndex(focusedUnitIndex), unitsList(unitsList), name(name) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            focusedUnitIndex = idx;
            //button->setProperty("NormalImage", "set:FTSUI image:full_image");
            return true;
        };
    };
}