#pragma once
#include <gtest/gtest.h>
#include "../src/Frontend/FrontendState.h"

TEST(FrontendLogicIntegration, GetResources)
{
	GameLogic logic("testAssets");
	FrontendState state(logic);
	auto resources = state.getResources();
	ASSERT_EQ(resources.size(), 4);
	ASSERT_EQ(resources.begin()->second, 0);
}

TEST(FrontendLogicIntegration, GetPlayerOnMove)
{
	GameLogic logic("testAssets");
	FrontendState state(logic);
	auto playerOnMove = state.getPlayerOnMove();
	ASSERT_EQ(playerOnMove, 0);
}
