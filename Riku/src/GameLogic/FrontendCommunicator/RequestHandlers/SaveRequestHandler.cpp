#include "SaveRequestHandler.h"

std::shared_ptr<Response> SaveRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
	return std::make_shared<Response>(request, true);
}

bool SaveRequestHandler::canHandle(const Request& request) const
{
	return true;
}
