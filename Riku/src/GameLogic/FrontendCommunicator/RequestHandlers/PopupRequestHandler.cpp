#include "PopupRequestHandler.h"
#include "../../Utils/LogicUtils.h"
#include "../Responses/StringResponse.h"
std::shared_ptr<Response> PopupRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<StringResponse>(request, LogicUtils::getPopup());
}

bool PopupRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "popup";
}
