#pragma once
#include "Request.h"
class TileRequest :
    public Request
{
    int mapX, mapY;
public:
    TileRequest(std::string key, int mapX, int mapY)
        : Request(key), mapX(mapX), mapY(mapY) {}

    int getMapX() { return mapX; }
    int getMapY() { return mapY; }

};

