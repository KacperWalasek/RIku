#pragma once
#include "../Move/IMove.h"
#include "../MoveDescriptions/IMoveDescription.h"

class IMoveDescriptionHandler
{
public:
	virtual std::shared_ptr<IMove> handleDescription(const IMoveDescription& description) = 0;
	virtual bool canHandle(const IMoveDescription& description) const = 0;
};

