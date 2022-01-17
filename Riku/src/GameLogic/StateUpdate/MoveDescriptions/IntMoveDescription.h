#pragma once
#include "IMoveDescription.h"
class IntMoveDescription :
    public IMoveDescription
{
    int value;
    std::string moveType;
public:
    IntMoveDescription(std::string moveType, int value)
        : value(value), moveType(moveType) {}
    virtual std::string getMoveType() const override { return moveType; }

    int get() const { return value; }
};

