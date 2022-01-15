#include "AvailableBuildingsRequestHandler.h"
#include "../Responses/StringStringMapResponse.h"
#include "../Requests/TileRequest.h"
#include "../../StateUpdate/Move/BuildTileObject.h"

std::shared_ptr<Response> AvailableBuildingsRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::shared_ptr<TileRequest> tileRequest = std::static_pointer_cast<TileRequest>(request);
    std::map<std::string, std::string> buildings;
    for (const auto& object : assets.tileObjects)
        buildings.emplace(object.first, object.second.getByKey("description").asString());

    std::map<std::string, std::string> availableBuildings;
    std::copy_if(buildings.begin(), buildings.end(),
        std::insert_iterator(availableBuildings, availableBuildings.end()),
        [&](const std::pair<std::string, std::string>& building) {
            //TODO index playera
            BuildTileObject obj(state.playerOnMove, { tileRequest->getMapX(), tileRequest->getMapY() }, building.first);
            return obj.isDoable(state, assets);
        });
    return std::make_shared<StringStringMapResponse>(tileRequest, availableBuildings);
}

bool AvailableBuildingsRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "available_buildings";
}
