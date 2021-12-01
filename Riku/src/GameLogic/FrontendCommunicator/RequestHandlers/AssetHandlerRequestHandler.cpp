#include "AssetHandlerRequestHandler.h"

AssetHandlerRequestHandler::AssetHandlerRequestHandler(const LogicAssets& assets)
    : assets(assets)
{}

std::shared_ptr<Response> AssetHandlerRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<AssetHandlerResponse>(request, assets.handler);
}

bool AssetHandlerRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "asset_handler";
}
