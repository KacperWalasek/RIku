#pragma once
#include "IRequestHandler.h"
#include "../Responses/StringResponse.h"
#include "../../../Network/NetworkUtils.h"
class IpRequestHandler :
    public IRequestHandler
{
public:
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override
    {
        return std::make_shared<StringResponse>(request, NetworkUtils::getIpAddress());
    }
    virtual bool canHandle(const Request& request) const override
    {
        return request.getKey() == "ip";
    }
};

