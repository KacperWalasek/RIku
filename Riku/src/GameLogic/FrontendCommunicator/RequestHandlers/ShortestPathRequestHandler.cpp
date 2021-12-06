#include "ShortestPathRequestHandler.h"
#include "../Requests/TilePairRequest.h"
#include "../Responses/PositionListResponse.h"
#include "../../LogicUtils.h"

ShortestPathRequestHandler::ShortestPathRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> ShortestPathRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::shared_ptr<TilePairRequest> tileRequest = std::static_pointer_cast<TilePairRequest>(request);
    return std::make_shared<PositionListResponse>(request,LogicUtils::getShortestPath(
        state,
        tileRequest->getFromX(), 
        tileRequest->getFromY(), 
        tileRequest->getToX(), 
        tileRequest->getToY()
    ));
}

bool ShortestPathRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "shortest_path";
}
