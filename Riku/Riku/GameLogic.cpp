// Kacper Walasek
#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
{
	resources.initialize();
	gameState.map = { 6, std::vector<Tile>() };
	gameState.players = { 2, (int)resources.playerResources.size() };


	for (std::vector<Tile>& row : gameState.map)
		for (int i = 0; i < 6; i++)
			row.push_back(Tile(4, resources.areas[0], resources.grounds[1], resources.biomes[0]));
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
	std::cout << "\t Try to use 10:"<< std::endl <<
		 std::boolalpha <<
		"\t\t return - " << gameState.players[0].useResources(woodIndex,10) << std::endl <<
		"\t\t quantity - " << gameState.players[0].getResourceQuantity(woodIndex) << std::endl;

	
}
