#pragma once
#include <gtest/gtest.h>
#include "../src/Frontend/FrontendState.h"

TEST(FrontendLogicIntegration, GetResources)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	auto resources = state.getResources();
	ASSERT_EQ(resources.size(), 4);
	ASSERT_EQ(resources.begin()->second, 0);
}

TEST(FrontendLogicIntegration, GetPlayerOnMove)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	auto playerOnMove = state.getPlayerOnMove();
	ASSERT_EQ(playerOnMove, 0);
}

TEST(FrontendLogicIntegration, CreateMiniGame)
{
	GameLogic logic("testAssets", "testMiniAssets");
	FrontendState state(logic);
	state.setHotseatPlayerCount(2);
	state.startGame();
	ASSERT_FALSE(state.isInMiniGame());
	state.attack(0, 0, 0, 1);
	ASSERT_TRUE(state.isInMiniGame());
	LogicUtils::resetPlayerIndexes();
}
