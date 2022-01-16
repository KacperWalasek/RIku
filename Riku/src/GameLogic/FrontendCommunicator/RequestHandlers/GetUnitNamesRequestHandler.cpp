#include "GetUnitNamesRequestHandler.h"
#include "../Responses/StringListResponse.h"

GetUnitNamesRequestHandler::GetUnitNamesRequestHandler(const LogicAssets& assets)
    : assets(assets)
{}

std::shared_ptr<Response> GetUnitNamesRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::vector<std::string> names;
    for (const auto& unit : assets.units)
        names.push_back(unit.first);
    return std::make_shared<StringListResponse>(request, names);
}

bool GetUnitNamesRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "unit_names";
}
