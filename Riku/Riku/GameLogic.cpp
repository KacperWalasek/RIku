// Kacper Walasek
#include "GameLogic.h"
#include <iostream>

GameLogic::GameLogic()
{
	resources.initialize();
	gameState.map = { 6, std::vector<Tile>() };
	for (std::vector<Tile>& row : gameState.map)
		for (int i = 0; i < 6; i++)
			row.push_back(Tile(4, resources.areas[0], resources.grounds[1], resources.biomes[0]));
	std::cout << "<GameLogic.cpp:10>" << std::endl << "Element mapy:" << std::endl <<
		"\t Biome - " << gameState.map[4][2].biome.getName() << std::endl <<
		"\t Area - " << gameState.map[4][2].area.getName() << std::endl <<
		"\t Ground - " << gameState.map[4][2].ground.getName() << std::endl <<
		"\t Cost - " << gameState.map[4][2].getCost() << std::endl;
}
