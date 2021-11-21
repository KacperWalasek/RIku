#pragma once
#include "IMoveDescription.h"
#include "../../Unit/Unit.h"

class TranslateUnitMoveDescription :
    public IMoveDescription
{
    int fromX, fromY, toX, toY;
public:
    TranslateUnitMoveDescription(int fromX, int fromY, int toX, int toY) 
        : fromX(fromX), fromY(fromY), toX(toX), toY(toY) {};
    virtual std::string getMoveType() const override { return "translate_unit"; }

    int getFromX() const { return fromX; }
    int getFromY() const { return fromY; }
    int getToX() const { return toX; }
    int getToY() const { return toY; }
};

