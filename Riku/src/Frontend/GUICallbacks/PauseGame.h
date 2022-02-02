#pragma once

#include <CEGUI/CEGUI.h>
#include "Functor.h"
namespace CEGUI::Functor {       

    class PauseGame : public Functor
    {
    private:
        bool& isGameActive;
        bool pauseGame;
    public:
        PauseGame(bool& isGameActive, bool pauseGame)
            : Functor(), isGameActive(isGameActive), pauseGame(pauseGame) {}

        bool operator()(const CEGUI::EventArgs& e)
        {
            isGameActive = !pauseGame;
            return true;
        }
    };
}