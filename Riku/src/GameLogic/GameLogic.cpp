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
#include "StateUpdate/Move/CreateUnit.h"
#include "StateUpdate/Move/BuildTileObject.h"

GameLogic::GameLogic() : stateUpdate(this->gameState)
{
	assets.initialize();

	gameState.map = { 6, std::vector<Tile>() };
	gameState.players = { 2, (int)assets.playerResources.size() };
	stateUpdate.setHandlers({ std::make_shared<PlayerPatchHandler>(),
							  std::make_shared<TilePatchHandler>() });


	for (std::vector<Tile>& row : gameState.map)
		for (int i = 0; i < 6; i++)
			row.push_back(Tile(4, assets.areas[0], assets.grounds[1], assets.biomes[0], 1));

	communicator.setHandlers({ std::make_shared<MapRequestHandler>(gameState.map) });

	std::cout << "<GameLogic.cpp>" << std::endl << "Element mapy:" << std::endl <<
		"\t Biome - " << gameState.map[4][2].biome.getName() << std::endl <<
		"\t Area - " << gameState.map[4][2].area.getName() << std::endl <<
		"\t Ground - " << gameState.map[4][2].ground.getName() << std::endl <<
		"\t Cost - " << gameState.map[4][2].getCost() << std::endl;

	int woodIndex = 0;
	std::cout << "Player test" << std::endl <<
		"\t Begining wood count - " << gameState.players[0].getResourceQuantity(woodIndex) << std::endl;
	gameState.players[0].acceptResources(woodIndex, 10);
	std::cout << "\t After adding 10 - " << gameState.players[0].getResourceQuantity(woodIndex) << std::endl;
	gameState.players[0].acceptResources(woodIndex, 10);
	gameState.players[0].useResources(woodIndex, 15);
	std::cout << "\t After adding 10 more and using 15 - " << gameState.players[0].getResourceQuantity(woodIndex) << std::endl;
	std::cout << "\t Try to use 10:" << std::endl <<
		std::boolalpha <<
		"\t\t return - " << gameState.players[0].useResources(woodIndex, 10) << std::endl <<
		"\t\t quantity - " << gameState.players[0].getResourceQuantity(woodIndex) << std::endl;

	std::cout << "Factory test" << std::endl;
	std::cout << "\t Btw. Tile 1,1 has some resources inside: " << assets.playerResources[gameState.map[1][1].resource].getName() << std::endl;
	auto m = std::map < std::string, sol::function >();
	gameState.map[1][1].object = std::make_shared<ResourceFactory>(std::make_shared<SimpleTileObject>("Stone main", m), 1, 10);
	gameState.map[1][1].object->onBeingPlaced(1, 1);

	std::cout << "\t Let's build main there: " << gameState.map[1][1].object->getName() << std::endl;
	std::cout << "\t Let's see what happens with " << assets.playerResources[1].getName() << " quantity: " << gameState.players[0].getResourceQuantity(1) << std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	std::cout << "\t First turn..." << gameState.players[0].getResourceQuantity(1) << std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	std::cout << "\t Second turn..." << gameState.players[0].getResourceQuantity(1) << std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	std::cout << "\t Third turn..." << gameState.players[0].getResourceQuantity(1) << std::endl;

	std::cout << "\t Let's see whats on 2,2 tile: " << assets.playerResources[gameState.map[2][2].resource].getName() << std::endl;

	std::shared_ptr<BuildTileObject> build = std::make_shared<BuildTileObject>(0, std::pair(2, 2), "wood_factory", assets);
	stateUpdate.handleMove(build);
	std::cout << "\t Let's build wood factory there for no reason: " << gameState.map[2][2].object->getName() << std::endl;
	std::cout << "\t Let's see what happens with (" << assets.playerResources[0].getName() << ',' << assets.playerResources[1].getName() << ") quantity."<< std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	stateUpdate.handleMove(gameState.map[2][2].object->onTurnEnd());
	std::cout << "\t First turn... (" << gameState.players[0].getResourceQuantity(0) << ',' << gameState.players[0].getResourceQuantity(1) << ")" << std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	stateUpdate.handleMove(gameState.map[2][2].object->onTurnEnd());
	std::cout << "\t Second turn...(" << gameState.players[0].getResourceQuantity(0) << ',' << gameState.players[0].getResourceQuantity(1) << ")" << std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	stateUpdate.handleMove(gameState.map[2][2].object->onTurnEnd());
	std::cout << "\t Third turn...(" << gameState.players[0].getResourceQuantity(0) << ',' << gameState.players[0].getResourceQuantity(1) << ")" << std::endl;
	gameState.map[2][2].resource = 0;
	std::cout << "\t I cheated a little and put wood in 2,2 tile: " << assets.playerResources[gameState.map[2][2].resource].getName() << std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	stateUpdate.handleMove(gameState.map[2][2].object->onTurnEnd());
	std::cout << "\t Forth turn...(" << gameState.players[0].getResourceQuantity(0) << ',' << gameState.players[0].getResourceQuantity(1) << ")" << std::endl;
	auto cu = std::make_shared<CreateUnit>(0,"stefan", assets);
	stateUpdate.handleMove(cu);

	stateUpdate.handleMove(gameState.players[0].units[0]->onTurnEnd());
}

std::shared_ptr<Response> GameLogic::getInfo(std::shared_ptr<Request> request)
{
	return communicator.handleRequest(request);
}
