#pragma once
#include <memory>
#include "IWinCondition.h"

class CombinedWinCondition : public IWinCondition
{
public:
	std::shared_ptr<IWinCondition> condition1;
	std::shared_ptr<IWinCondition> condition2;

	CombinedWinCondition(std::shared_ptr<IWinCondition> condition1, std::shared_ptr<IWinCondition> condition2)
		: condition1(condition1), condition2(condition2) {}
	virtual int isSatisfied(const GameState& state, const LogicAssets& assets)
	{
		int p1 = condition1->isSatisfied(state,assets);
		return p1 == -1 ? condition2->isSatisfied(state, assets) : p1;
	}
};
