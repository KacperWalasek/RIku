#include "MapRequestHandler.h"
#include "MapResponse.h"



std::shared_ptr<Response> MapRequestHandler::handleRequest(std::shared_ptr<Request> request)
{
    return std::make_shared<MapResponse>(request, map);
}

bool MapRequestHandler::canHandle(const Request& request) const
{
    return request.getKey()=="map";
}
