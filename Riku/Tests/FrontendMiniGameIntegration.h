#pragma once
#include <gtest/gtest.h>
#include "../src/Frontend/FrontendState.h"
#include "../src/MiniGame/Unit/MiniUnit.h"

TEST(FrontendLogicIntegration, GetMiniGameMap)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	auto minimap = state.getMiniMap();
	ASSERT_NE(minimap.size(), 0);
	ASSERT_NE(minimap[0].size(), 0);
	ASSERT_NE(minimap[0][0].unit, nullptr);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, CreatingMiniUnits)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(2);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	auto minimap = state.getMiniMap();
	ASSERT_NE(minimap[0][0].unit, nullptr);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, GetMiniUnits)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	auto units = state.getMiniUnits();
	ASSERT_EQ(units.size(), 3);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, GetShortestPathInMinigame)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	auto path = state.getShortestPath(0,0,2,2);
	ASSERT_EQ(path.cost, 4);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, FinishMinigameTurn)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(2);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	ASSERT_EQ(state.getPlayerOnMove(), 0);
	state.finishTurn();
	ASSERT_TRUE(state.isInMiniGame());
	ASSERT_EQ(state.getPlayerOnMove(), 1);
	state.finishTurn();
	ASSERT_TRUE(state.isInMiniGame());
	ASSERT_EQ(state.getPlayerOnMove(), 0);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, MoveMiniUnit)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	auto unit = state.getMiniMap()[0][0].unit;
	ASSERT_NE(unit, nullptr);
	int mp = unit->movementPoints;
	state.moveUnit(0, 0, 1, 3);
	auto map = state.getMiniMap();
	ASSERT_EQ(map[0][0].unit, nullptr);
	ASSERT_NE(map[1][3].unit, nullptr);
	ASSERT_EQ(map[1][3].unit->movementPoints, mp - 4);
	auto units = state.getMiniUnits();
	ASSERT_EQ(units.size(), 3);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, MiniGameAttack)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	state.moveUnit(0, 0, 0, 18);
	auto map = state.getMiniMap();
	ASSERT_NE(map[0][18].unit, nullptr);
	ASSERT_NE(map[0][19].unit, nullptr);
	state.attack(0, 18, 0, 19);
	map = state.getMiniMap();
	ASSERT_NE(map[0][18].unit, nullptr);
	ASSERT_EQ(map[0][19].unit, nullptr);
	
	state.finishTurn();
	auto units = state.getMiniUnits();
	ASSERT_EQ(units.size(), 2);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, ResignMiniGame)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	state.resign();
	ASSERT_FALSE(state.isInMiniGame());
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, WinMiniGame)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	state.moveUnit(0, 0, 0, 18);
	state.attack(0, 18, 0, 19);
	state.moveUnit(0, 18, 1, 18);
	state.attack(1, 18, 1, 19);
	state.moveUnit(1, 18, 2, 18);
	state.attack(2, 18, 2, 19);
	state.finishTurn();
	ASSERT_FALSE(state.isInMiniGame());
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, getSkill)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.build("test_tile_object", 0, 0);
	state.choseGuiOption(0, 0, 0);
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	ASSERT_EQ(state.getSkills().size(), 1);
	LogicUtils::resetPlayerIndexes();
}

TEST(FrontendLogicIntegration, useSkill)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(3);
	state.startGame();
	state.build("test_tile_object", 0, 0);
	state.choseGuiOption(0, 0, 0);
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	state.useSkill("test_skill",2,2);
	ASSERT_FALSE(state.isInMiniGame());
	LogicUtils::resetPlayerIndexes();
}