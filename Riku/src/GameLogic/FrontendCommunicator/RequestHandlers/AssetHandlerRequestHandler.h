#pragma once
#include "IRequestHandler.h"
#include "../../LogicAssets.h"
#include "../Responses/AssetHandlerResponse.h"

class AssetHandlerRequestHandler :
    public IRequestHandler
{
    const LogicAssets& assets;
public:
    AssetHandlerRequestHandler(const LogicAssets& assets);
    // Odziedziczono za poœrednictwem elementu IRequestHandler
    virtual std::shared_ptr<Response> handleRequest(std::shared_ptr<Request> request) const override;
    virtual bool canHandle(const Request& request) const override;
};

