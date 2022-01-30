#pragma once
#include <gtest/gtest.h>
#include "../src/GameLogic/LogicAssets.h"

TEST(ReadingAssets, Biome) {
	LogicAssets assets;
	assets.initialize("testAssets", "testMiniAssets");

	ASSERT_EQ(assets.biomes.size(), 3);
	ASSERT_EQ(assets.biomes.at("biome2").getModifiedCost(1), 1.2);
}

TEST(ReadingAssets, Area) {
	LogicAssets assets;
	assets.initialize("testAssets", "testMiniAssets");

	ASSERT_EQ(assets.areas.size(), 2);
	ASSERT_EQ(assets.areas.at("area2").getModifiedCost(1), 1.1);
}

TEST(ReadingAssets, Ground) {
	LogicAssets assets;
	assets.initialize("testAssets", "testMiniAssets");

	ASSERT_EQ(assets.grounds.size(), 3);
	ASSERT_EQ(assets.grounds.at("ground2").getCost(), 2);
}

TEST(ReadingAssets, Resource) {
	LogicAssets assets;
	assets.initialize("testAssets", "testMiniAssets");

	ASSERT_EQ(assets.playerResources.size(), 4);
	ASSERT_EQ(assets.playerResources[1].getName(), "resource2");
}


TEST(ReadingAssets, Unit) {
	LogicAssets assets;
	assets.initialize("testAssets", "testMiniAssets");

	ASSERT_EQ(assets.units.size(), 1);
	ASSERT_EQ(assets.units.begin()->first, "stefan");
}
