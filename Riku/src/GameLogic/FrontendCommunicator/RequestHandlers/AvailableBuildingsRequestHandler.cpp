#include "AvailableBuildingsRequestHandler.h"
#include "../Responses/StringListResponse.h"

std::shared_ptr<Response> AvailableBuildingsRequestHandler::handleRequest(std::shared_ptr<Request> request)
{
    std::vector<std::string> names;
    std::transform(assets.tileObjects.begin(), assets.tileObjects.end(),
        std::back_insert_iterator(names),
        [](const auto& pair) {
            return pair.first;
        });
    return std::make_shared<StringListResponse>(request, names);
}

bool AvailableBuildingsRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "available_buildings";
}
