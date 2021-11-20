#pragma once
#include "IRequestHandler.h"
#include "../../LogicAssets.h"

class AvailableBuildingsRequestHandler :
    public IRequestHandler
{
    LogicAssets& assets;
public:
    AvailableBuildingsRequestHandler(LogicAssets& assets) : assets(assets) {};
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) override;
    virtual bool canHandle(const Request& request) const override;
};
