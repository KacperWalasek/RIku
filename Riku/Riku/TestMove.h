#pragma once
#include "../src/GameLogic/StateUpdate/Move/IMove.h"
#include "../src/GameLogic/StateUpdate/Patch/Patch.h"
class TestMove : public IMove
{
public:
	// Odziedziczono za poœrednictwem elementu IMove
	virtual std::shared_ptr<Patch> createPatch(const GameState& state) const override;
	virtual bool isDoable(const GameState& state) const override;
};

