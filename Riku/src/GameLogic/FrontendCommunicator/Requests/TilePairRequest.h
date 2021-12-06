#pragma once
#include "Request.h"
class TilePairRequest :
    public Request
{
    int fromX, fromY, toX, toY;
public:
    TilePairRequest(std::string key, int fromX, int fromY, int toX, int toY) 
        : Request(key), fromX(fromX), fromY(fromY), toX(toX), toY(toY)
    {}
    int getFromX() { return fromX; }
    int getFromY() { return fromY; }
    int getToX() { return toX; }
    int getToY() { return toY; }
};

