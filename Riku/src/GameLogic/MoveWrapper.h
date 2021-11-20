#pragma once
#include <memory>
#include "StateUpdate/Move/IMove.h"
class MoveWrapper
{
public:
	std::shared_ptr<IMove> move;
	MoveWrapper(IMove& m) {
		move = m.asPointner();
	}
};

