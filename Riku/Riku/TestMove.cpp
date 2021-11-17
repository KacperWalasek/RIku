#include "TestMove.h"
#include <iostream>

std::shared_ptr<Patch> TestMove::createPatch(const GameState& state) const
{
    std::cout << "test move" << std::endl;
    return std::shared_ptr<Patch>();
}

bool TestMove::isDoable(const GameState& state) const
{
    return false;
}
