#pragma once
#include "IMove.h"
#include "../Patch/Patch.h"

class TestMove : public IMove
{
	std::string message;
public:
	TestMove(std::string message = "") : message(message) {}
	// Odziedziczono za poœrednictwem elementu IMove
	virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
	virtual bool isDoable(const GameState& state, const LogicAssets& assets, bool popup = false) const override;
	virtual std::shared_ptr<IMove> asPointner() const override;
};

