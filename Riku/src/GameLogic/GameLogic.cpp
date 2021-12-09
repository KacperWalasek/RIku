// Kacper Walasek
#include "GameLogic.h"
#include <iostream>
#include <memory>
#include "StateUpdate/Move/CreateUnit.h"
#include "Tile/MapGenerator.h"
#include "StateUpdate/MoveFactory/TestMoveHandler.h"
#include "StateUpdate/MoveFactory/BuildMoveHandler.h"
#include "StateUpdate/MoveFactory/TranslateUnitMoveHandler.h"
#include "StateUpdate/MoveFactory/ChoseGuiOptionMoveHandler.h"
#include "StateUpdate/MoveFactory/FinishGameMoveHandler.h"

#include "StateUpdate/PatchHandler/PlayerOnMovePatchHandler.h"
#include "StateUpdate/PatchHandler/PlayerPatchHandler.h"
#include "StateUpdate/PatchHandler/TilePatchHandler.h"
#include "StateUpdate/PatchHandler/RegisterHookablePatchHandler.h"

#include "FrontendCommunicator/RequestHandlers/AvailableBuildingsRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerUnitsRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerResourcesRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/AssetHandlerRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerOnMoveRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/ShortestPathRequestHandler.h"
#include "StateUpdate/PatchHandler/UnitPatchHandler.h"
#include "FrontendCommunicator/RequestHandlers/TileObjectGuiRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/MapRequestHandler.h"
#include "FrontendCommunicator/Responses/MapResponse.h"

GameLogic::GameLogic() : stateUpdate(this->gameState, this->assets)
{
	assets.initialize();

	gameState.map = { 6, std::vector<Tile>() };
	gameState.players = { (int)assets.playerResources.size(), (int)assets.playerResources.size() };
  
	stateUpdate.setHandlers({ 
		std::make_shared<PlayerPatchHandler>(),
		std::make_shared<TilePatchHandler>(),
		std::make_shared<RegisterHookablePatchHandler>(),
		std::make_shared<PlayerOnMovePatchHandler>(),
		std::make_shared<UnitPatchHandler>()
		});

	factory.setHandlers({ 
		std::make_shared<TestMoveHandler>(),
		std::make_shared<BuildMoveHandler>(gameState),
		std::make_shared<TranslateUnitMoveHandler>(),
		std::make_shared<FinishGameMoveHandler>(),
		std::make_shared<ChoseGuiOptionMoveHandler>(gameState)
		});

	communicator.setHandlers({
		std::make_shared<MapRequestHandler>(gameState.map),
		std::make_shared<AvailableBuildingsRequestHandler>(gameState,assets),
		std::make_shared<PlayerUnitsRequestHandler>(gameState),
		std::make_shared<PlayerResourcesRequestHandler>(gameState, assets),
		std::make_shared<AssetHandlerRequestHandler>(assets),
		std::make_shared<PlayerOnMoveRequestHandler>(gameState),
		std::make_shared<ShortestPathRequestHandler>(gameState),
		std::make_shared<TileObjectGuiRequestHandler>(gameState)
		});
	
	MapGenerator generator(assets.mapGenerator);
	gameState.map = generator.getMap(assets);

	auto unitMove = std::make_shared<CreateUnit>(0, "stefan", 10, 10);
	stateUpdate.handleMove(unitMove);
	unitMove = std::make_shared<CreateUnit>(0, "stefan", 11, 10);
	stateUpdate.handleMove(unitMove);
	unitMove = std::make_shared<CreateUnit>(1, "stefan", 14, 14);
	stateUpdate.handleMove(unitMove);
}

std::shared_ptr<Response> GameLogic::getInfo(std::shared_ptr<Request> request) const
{
	return communicator.handleRequest(request);
}

void GameLogic::makeMove(std::shared_ptr<IMoveDescription> moveDescription)
{
	stateUpdate.handleMove(factory.createMove(*moveDescription));
}

bool GameLogic::isMoveLegal(std::shared_ptr<IMoveDescription> moveDescription) const
{
	std::shared_ptr<IMove> move = factory.createMove(*moveDescription);
	if (!move)
		return false;
	return move->isDoable(gameState, assets);
}
