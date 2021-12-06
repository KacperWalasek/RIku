#pragma once
#include "IMoveDescription.h"
class ChoseGuiOptionMoveDescription :
    public IMoveDescription
{
    int index;
    int mapX;
    int mapY;
public:
    ChoseGuiOptionMoveDescription(int mapX, int mapY, int index) : index(index), mapX(mapX), mapY(mapY) {}
    virtual std::string getMoveType() const override { return "chose_gui_option"; }

    int getMapX() const { return mapX; }
    int getMapY() const { return mapY; }
    int getIndex() const { return index; }
};

