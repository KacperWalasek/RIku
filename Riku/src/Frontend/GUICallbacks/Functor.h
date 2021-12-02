#pragma once

#include <CEGUI/CEGUI.h>

namespace CEGUI::Functor {

    class Functor
    {
    public:     
        Functor() {}
        virtual bool operator()(const CEGUI::EventArgs& e) { return true; }
        
    };
}