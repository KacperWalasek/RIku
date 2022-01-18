#pragma once

class GameState;
class LogicAssets;
class IWinCondition
{
public:
	virtual int isSatisfied(const GameState& state, const LogicAssets& assets) = 0;
};