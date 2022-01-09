#include "ShortestPathRequestHandler.h"
#include "../Requests/TilePairRequest.h"
#include "../Responses/PathResponse.h"
#include "../../Utils/LogicUtils.h"
#include "../../Unit/Unit.h"

ShortestPathRequestHandler::ShortestPathRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> ShortestPathRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::shared_ptr<TilePairRequest> tileRequest = std::static_pointer_cast<TilePairRequest>(request);
    auto unit = state.map[tileRequest->getFromX()][tileRequest->getFromY()].unit;
    int mp = unit ? unit->movementPoints : 0;
    return std::make_shared<PathResponse>(request,LogicUtils::getShortestPath(
        state,
        tileRequest->getFromX(), 
        tileRequest->getFromY(), 
        tileRequest->getToX(), 
        tileRequest->getToY(),
        mp
    ));
}

bool ShortestPathRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "shortest_path";
}
