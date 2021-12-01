#pragma once
#include "Response.h"
#include "../../Assets/AssetHandler.h"
class AssetHandlerResponse :
    public Response
{ 
    const logic::AssetHandler& handler;
public:
    AssetHandlerResponse(std::shared_ptr<Request> request, const logic::AssetHandler& handler)
        : Response(request, true), handler(handler) {}
    const logic::AssetHandler& getHandler() { return handler; }
};

