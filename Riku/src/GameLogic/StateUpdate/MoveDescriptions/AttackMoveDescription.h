#pragma once
#include "IMoveDescription.h"
class AttackMoveDescription :
    public IMoveDescription
{
    int fromX, fromY, toX, toY;
public:
    AttackMoveDescription(int fromX, int fromY, int toX, int toY)
        : fromX(fromX), fromY(fromY), toX(toX), toY(toY) {}
    virtual std::string getMoveType() const override { return "attack"; }

    int getFromX() const { return fromX; }
    int getFromY() const { return fromY; }
    int getToX() const { return toX; }
    int getToY() const { return toY; }
};
