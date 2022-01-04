#pragma once
#include <vector>
#include "../src/GameLogic/Tile/Tile.h"

Biome testBiome = Biome("name", 2);
Area testArea = Area("name", 2.2);
Ground testGround = Ground("name", 1.1);

std::vector<std::vector<Tile>> createTestMap() {
	std::vector<std::vector<Tile>> map;
	for (int i = 0; i < 5; i++) {
		map.emplace_back();
		for (int j = 0; j < 5; j++)
			map[i].emplace_back(i, testArea, testGround, testBiome, j);
	}
	return map;
}