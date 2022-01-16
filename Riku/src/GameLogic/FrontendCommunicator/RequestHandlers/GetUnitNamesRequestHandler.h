#pragma once
#include "IRequestHandler.h"
#include "../../LogicAssets.h"
class GetUnitNamesRequestHandler :
    public IRequestHandler
{
    const LogicAssets& assets;
public:
    GetUnitNamesRequestHandler(const LogicAssets& assets);
    // Odziedziczono za po�rednictwem elementu IRequestHandler
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

