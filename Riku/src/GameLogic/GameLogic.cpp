// Kacper Walasek
#include "GameLogic.h"
#include <iostream>
#include <memory>
#include "GameObject/SimpleTileObject.h"
#include "StateUpdate/Move/ExtractResources.h"
#include "StateUpdate/PatchHandler/PlayerPatchHandler.h"
#include "StateUpdate/PatchHandler/TilePatchHandler.h"
#include "GameObject/ResourceFactory.h"
#include "FrontendCommunicator/RequestHandlers/MapRequestHandler.h"
#include "FrontendCommunicator/Responses/MapResponse.h"
#include "StateUpdate/MoveFactory/TestMoveHandler.h"
#include "StateUpdate/MoveDescriptions/SimpleMoveDescription.h"
#include "StateUpdate/Move/CreateUnit.h"
#include "StateUpdate/Move/BuildTileObject.h"
#include "FrontendCommunicator/RequestHandlers/AvailableBuildingsRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerUnitsRequestHandler.h"
#include "FrontendCommunicator/RequestHandlers/PlayerResourcesRequestHandler.h"
#include "StateUpdate/MoveFactory/BuildMoveHandler.h"
#include "StateUpdate/MoveFactory/TranslateUnitMoveHandler.h"
#include "Tile/TileDescription.h"
#include "Tile/MapGenerator.h"

GameLogic::GameLogic() : stateUpdate(this->gameState, this->assets)
{
	assets.initialize();

	gameState.map = { 6, std::vector<Tile>() };
	gameState.players = { (int)assets.playerResources.size(), (int)assets.playerResources.size() };
  
	stateUpdate.setHandlers({ std::make_shared<PlayerPatchHandler>(),
							  std::make_shared<TilePatchHandler>() });
	factory.setHandlers({ 
		std::make_shared<TestMoveHandler>(),
		std::make_shared<BuildMoveHandler>(),
		std::make_shared<TranslateUnitMoveHandler>()
		});

	communicator.setHandlers({ 
		std::make_shared<MapRequestHandler>(gameState.map),
		std::make_shared<AvailableBuildingsRequestHandler>(gameState,assets),
		std::make_shared<PlayerUnitsRequestHandler>(gameState),
		std::make_shared<PlayerResourcesRequestHandler>(gameState, assets)
		});
	
	MapGenerator generator(assets.mapGenerator);
	gameState.map = generator.getMap(assets);

	auto unitMove = std::make_shared<CreateUnit>(0, "stefan", 10, 10);
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
