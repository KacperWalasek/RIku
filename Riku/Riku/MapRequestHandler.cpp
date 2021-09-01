#include "MapRequestHandler.h"
#include "MapResponse.h"



Response* MapRequestHandler::handleRequest(std::shared_ptr<Request> request)
{
    return new MapResponse(request, map);
}

bool MapRequestHandler::canHandle(const Request& request) const
{
    return request.getKey()=="map";
}
