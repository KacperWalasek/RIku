// Kacper Walasek
#include "GameLogic.h"
#include <iostream>
#include <memory>
#include "SimpleTileObject.h"
#include "GenerateResources.h"
#include "PlayerPatchHandler.h"
#include "ResourceFactory.h"
#include "MapRequestHandler.h"
#include "MapResponse.h"

GameLogic::GameLogic() : stateUpdate(this->gameState)
{
	assets.initialize();
	gameState.map = { 6, std::vector<Tile>() };
	gameState.players = { 2, (int)assets.playerResources.size() };
	stateUpdate.setHandlers({ std::make_shared<PlayerPatchHandler>(PlayerPatchHandler()) });

	SimpleTileObject obj = SimpleTileObject("jakiesImie");

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

	gameState.map[1][1].object = std::make_shared<ResourceFactory>(std::make_shared<SimpleTileObject>("Stone main"), 1, 10);
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
	gameState.map[2][2].object = std::make_shared<ResourceFactory>(std::make_shared<SimpleTileObject>("Wood main"), 0, 10);
	gameState.map[2][2].object->onBeingPlaced(2, 2);
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
	std::cout << "\t I cheted a little and put wood in 2,2 tile: " << assets.playerResources[gameState.map[2][2].resource].getName() << std::endl;
	stateUpdate.handleMove(gameState.map[1][1].object->onTurnEnd());
	stateUpdate.handleMove(gameState.map[2][2].object->onTurnEnd());
	std::cout << "\t Forth turn...(" << gameState.players[0].getResourceQuantity(0) << ',' << gameState.players[0].getResourceQuantity(1) << ")" << std::endl;
}

std::shared_ptr<Response> GameLogic::getInfo(std::shared_ptr<Request> request)
{
	return communicator.handleRequest(request);
}
