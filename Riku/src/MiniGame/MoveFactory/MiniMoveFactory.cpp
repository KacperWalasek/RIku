#include "MiniMoveFactory.h"

std::shared_ptr<minigame::IMiniMove> minigame::MiniMoveFactory::createMove(const IMoveDescription& description) const
{
	for (std::shared_ptr<IMiniMoveDescriptionHandler> handler : handlers)
	{
		if (handler->canHandle(description))
			return handler->handleDescription(description);
	}
	return nullptr;
}

void minigame::MiniMoveFactory::setHandlers(std::vector<std::shared_ptr<IMiniMoveDescriptionHandler>>&& handlers)
{
	this->handlers = std::move(handlers);
}
