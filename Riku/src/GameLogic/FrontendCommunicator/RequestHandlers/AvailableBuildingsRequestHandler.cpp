#include "AvailableBuildingsRequestHandler.h"
#include "../Responses/StringListResponse.h"
#include "../Requests/TileRequest.h"
#include "../../StateUpdate/Move/BuildTileObject.h"

std::shared_ptr<Response> AvailableBuildingsRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::shared_ptr<TileRequest> tileRequest = std::static_pointer_cast<TileRequest>(request);
    std::vector<std::string> names;
    std::transform(assets.tileObjects.begin(), assets.tileObjects.end(),
        std::back_insert_iterator(names),
        [](const auto& pair) {
            return pair.first;
        });

    std::vector<std::string> availableNames;
    std::copy_if(names.begin(), names.end(),
        std::back_insert_iterator(availableNames),
        [&tileRequest, this](const auto& name) {
            //TODO index playera
            BuildTileObject obj(state.playerOnMove, { tileRequest->getMapX(), tileRequest->getMapY() }, name);
            return obj.isDoable(state, assets);
        });
    return std::make_shared<StringListResponse>(tileRequest, availableNames);
}

bool AvailableBuildingsRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "available_buildings";
}
