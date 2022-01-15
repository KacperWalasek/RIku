#pragma once
#include "Response.h"
#include "../../Assets/AssetHandler.h"
class AssetHandlerResponse :
    public Response
{ 
    const logic::AssetHandler& logicHandler;
    const logic::AssetHandler& minigameHandler;
public:
    AssetHandlerResponse(std::shared_ptr<Request> request, const logic::AssetHandler& logicHandler, const logic::AssetHandler& minigameHandler)
        : Response(request, true), logicHandler(logicHandler), minigameHandler(minigameHandler) {}
    const logic::AssetHandler& getLogicHandler() { return logicHandler; }
    const logic::AssetHandler& getMinigameHandler() { return minigameHandler; }
};

