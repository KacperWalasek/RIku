#pragma once
#include <vector>
#include <memory>
#include "IMiniMoveDescriptionHandler.h"

class IMoveDescription;
class IMiniMove;
class MiniMoveFactory
{
	std::vector<std::shared_ptr<IMiniMoveDescriptionHandler>> handlers;
public:
	std::shared_ptr<IMiniMove> createMove(const IMoveDescription& description) const;
	void setHandlers(std::vector<std::shared_ptr<IMiniMoveDescriptionHandler>>&& handlers);
};

