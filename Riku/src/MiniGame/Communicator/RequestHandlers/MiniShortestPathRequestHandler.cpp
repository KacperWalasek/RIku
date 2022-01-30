#include "MiniShortestPathRequestHandler.h"
#include "../../../GameLogic/FrontendCommunicator/Requests/TilePairRequest.h"
#include "../../../GameLogic/FrontendCommunicator/Responses/PathResponse.h"
#include "../../Utils/MiniGameUtils.h"
#include "../../Unit/MiniUnit.h"

minigame::MiniShortestPathRequestHandler::MiniShortestPathRequestHandler(const MiniGameState& state)
    : state(state) {}

std::shared_ptr<Response> minigame::MiniShortestPathRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::shared_ptr<TilePairRequest> tileRequest = std::static_pointer_cast<TilePairRequest>(request);
    auto unit = state.map[tileRequest->getFromX()][tileRequest->getFromY()].unit;
    int mp = unit ? unit->movementPoints : 0;
    return std::make_shared<PathResponse>(request,MiniGameUtils::getShortestPath(
        state,
        tileRequest->getFromX(), 
        tileRequest->getFromY(), 
        tileRequest->getToX(), 
        tileRequest->getToY(),
        mp
    ));
}

bool minigame::MiniShortestPathRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "shortest_path";
}
