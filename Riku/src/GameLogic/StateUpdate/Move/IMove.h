//Kacper Walasek
#pragma once
#include <memory>

class Patch;
class GameState;
class LogicAssets;
class Patch;
class IMove
{
public:	
	virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const = 0;
	virtual bool isDoable(const GameState& state, const LogicAssets& assets, bool popup = false) const = 0;
	virtual std::shared_ptr<IMove> asPointner() const = 0;
};

