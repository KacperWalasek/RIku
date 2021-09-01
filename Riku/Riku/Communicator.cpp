#include "Communicator.h"

Communicator::Communicator() 
{}

Communicator::~Communicator()
{
	for (IRequestHandler* handler : handlers)
		delete handler;
}

bool Communicator::canHandle(const Request & request) const
{
	for (IRequestHandler* handler : handlers)
		if (handler->canHandle(request))
			return true;
	return false;
}

void Communicator::setHandlers(std::vector<IRequestHandler*>&& handlers)
{
	this->handlers = std::move(handlers);
}

Response*  Communicator::handleRequest(std::shared_ptr<Request> request)
{
	for (IRequestHandler* handler : handlers)
	{
		if (handler->canHandle(*request))
			return handler->handleRequest(request);
	}
	return new Response(request, 1);
}
