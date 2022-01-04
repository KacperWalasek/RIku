#pragma once
#include <gtest/gtest.h>
#include "Mocks.h"
#include "../src/GameLogic/Player/Player.h"

TEST(PLAYER, INITIALIZATION) {
	Player player(3);
	ASSERT_EQ(player.getResourceQuantities().size(), 3);
}

TEST(PLAYER, ADD_RESOURCES) {
	Player player(2);
	player.acceptResources(0, 10);
	player.acceptResources(1, 5);
	ASSERT_EQ(player.getResourceQuantity(0), 10);
	ASSERT_EQ(player.getResourceQuantity(1), 5);
}

TEST(PLAYER, USE_RESOURCES) {
	Player player(2);
	player.acceptResources(0, 10);
	ASSERT_EQ(player.getResourceQuantity(0), 10);
	player.useResources(0, 5);
	ASSERT_EQ(player.getResourceQuantity(0), 5);
}

TEST(PLAYER, USE_MORE_RESOURCES_THAN_HAVE) {
	Player player(2);
	player.useResources(0, 5);
	ASSERT_EQ(player.getResourceQuantity(0), 0);
}

TEST(PLAYER, ADD_UNIT) {
	Player player(2);
	auto mock = std::make_shared<MockUnit>();
	player.addUnit(mock);
	ASSERT_EQ(player.units.size(), 1);
	ASSERT_EQ(player.units[0], mock);
}
