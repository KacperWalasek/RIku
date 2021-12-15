#pragma once
#include <memory>
#include "../StateUpdate/Move/IMiniMove.h"

class MiniMoveWrapper
{
public:
	std::shared_ptr<IMiniMove> move;
	MiniMoveWrapper(IMiniMove& m) {
		move = m.asPointner();
	}
};

