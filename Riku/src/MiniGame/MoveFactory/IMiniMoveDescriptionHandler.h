#pragma once
#include <memory>
#include "../../GameLogic/StateUpdate/MoveDescriptions/IMoveDescription.h"
#include "../StateUpdate/Move/IMiniMove.h"

class IMiniMoveDescriptionHandler
{
public:
	virtual std::shared_ptr<IMiniMove> handleDescription(const IMoveDescription& description) = 0;
	virtual bool canHandle(const IMoveDescription& description) const = 0;
};

