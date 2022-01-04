#pragma once
#include <gtest/gtest.h>
#include "../src/GameLogic/Tile/TileCost/Area.h"
#include "../src/GameLogic/Tile/TileCost/Ground.h"
#include "../src/GameLogic/Tile/TileCost/Biome.h"
#include "../src/GameLogic/Tile/Tile.h"

TEST(Tile, AreaCostModification) {
	Area area("name", 1.5);
	ASSERT_DOUBLE_EQ(area.getModifiedCost(1.3), 1.3*1.5);
}

TEST(Tile, AreaCostLowwerThanOne) {
	Area area("name", 0.5);
	ASSERT_DOUBLE_EQ(area.getModifiedCost(1), 1);
}

TEST(Tile, GroundCostModification) {
	Ground ground("name", 0.5);
	ASSERT_DOUBLE_EQ(ground.getModifiedCost(0.3), 0.3*0.5);
}

TEST(Tile, BiomeCost) {
	Biome biome("name", 2);
	ASSERT_EQ(biome.getCost(), 2);
}

TEST(Tile, GetCost) {
	Area area("name", 1.5);
	Ground ground("name", 0.5);
	Biome biome("name", 5);
	Tile tile(1,area,ground,biome);
	ASSERT_DOUBLE_EQ(tile.getCost(), 5 * 1.5 * 0.5);
}

