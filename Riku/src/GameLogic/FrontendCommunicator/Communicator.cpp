//Kacper Walasek
#include "Communicator.h"

Communicator::Communicator() 
{}

bool Communicator::canHandle(const Request & request) const
{
	for (std::shared_ptr<IRequestHandler> handler : handlers)
		if (handler->canHandle(request))
			return true;
	return false;
}

void Communicator::setHandlers(std::vector<std::shared_ptr<IRequestHandler>>&& handlers)
{
	this->handlers = std::move(handlers);
}

std::shared_ptr<Response> Communicator::handleRequest(std::shared_ptr<Request> request)
{
	for (std::shared_ptr<IRequestHandler> handler : handlers)
	{
		if (handler->canHandle(*request.get()))
			return handler->handleRequest(request);
	}
	return std::make_shared<Response>(request, false);
}
