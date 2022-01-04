#include "TileObjectGuiRequestHandler.h"
#include "../Requests/TileRequest.h"
#include "../Responses/StringListResponse.h"
#include "../../Hooks/GUIDescription.h"

TileObjectGuiRequestHandler::TileObjectGuiRequestHandler(const GameState& state)
    : state(state)
{}

std::shared_ptr<Response> TileObjectGuiRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::shared_ptr<TileRequest> tileRequest = std::static_pointer_cast<TileRequest>(request);
    std::shared_ptr<ITileObject> object = state.map[tileRequest->getMapX()][tileRequest->getMapY()].object;
    if (!object)
        return std::make_shared<Response>(request, false);
    return std::make_shared<StringListResponse>(request, object->getGuiDescription().getOptions());
}

bool TileObjectGuiRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "tile_object_gui";
}
