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
	ASSERT_FALSE(state.isInMiniGame());
	// TODO: make this number more sensible. Make unit in assets not have to be stefan
	state.attack(11, 10, 12, 10);
	ASSERT_TRUE(state.isInMiniGame());
}
