#pragma once
#include "IMoveDescription.h"

class BuildMoveDescription :
    public IMoveDescription
{
    std::string building;
    int mapX;
    int mapY;
public:
    BuildMoveDescription(std::string building, int mapX, int mapY) : building(building), mapX(mapX), mapY(mapY) {}
    virtual std::string getMoveType() const override { return "build"; }

    int getMapX() const { return mapX; }
    int getMapY() const { return mapY; }
    std::string getBuilding() const { return building; }
};
