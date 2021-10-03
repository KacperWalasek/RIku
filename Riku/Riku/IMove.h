//Kacper Walasek
#pragma once
#include "GameState.h"

class IMove
{
public:	
	virtual int apply(GameState& state) const = 0;
	virtual bool isDoable(const GameState& state) const = 0;
};

