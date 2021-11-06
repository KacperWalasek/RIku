#include "MoveFactory.h"

std::shared_ptr<IMove> MoveFactory::createMove(const IMoveDescription& description) const
{
	for (std::shared_ptr<IMoveDescriptionHandler> handler : handlers)
	{
		if (handler->canHandle(description))
			return handler->handleDescription(description);
	}
	return nullptr;
}

void MoveFactory::setHandlers(std::vector<std::shared_ptr<IMoveDescriptionHandler>>&& handlers)
{
	this->handlers = std::move(handlers);
}
