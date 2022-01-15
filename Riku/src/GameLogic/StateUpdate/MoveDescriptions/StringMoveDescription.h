#pragma once
#include "IMoveDescription.h"
class StringMoveDescription :
    public IMoveDescription
{
    std::string name;
    std::string moveType;
public:
    StringMoveDescription(std::string moveType, std::string name)
        : name(name), moveType(moveType) {}
    virtual std::string getMoveType() const override { return moveType; }

    std::string get() const { return name; }
};

