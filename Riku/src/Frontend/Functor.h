#pragma once
#include <CEGUI\EventArgs.h>

namespace CEGUI::Functor {
    class GUIFactory;
    class Functor
    {
    public:
        Functor(const GUIFactory& factory) {}
        virtual bool operator()(const CEGUI::EventArgs& e) { return true; }

    };
}