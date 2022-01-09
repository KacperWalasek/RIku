#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/GameLogic/GameState.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/PlayerOnMovePatchHandler.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/PlayerPatchHandler.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/RegisterHookablePatchHandler.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/TilePatchHandler.h"
#include "Utils.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/UnitPatchHandler.h"
#include "../src/GameLogic/Utils/LogicUtils.h"

TEST(PlayerOnMovePatchHandler, SetPlayerOnMove) 
{
	GameState state;
	state.players = { {3}, {3}, {3} };
	Patch patch(1);
	PlayerOnMovePatchHandler handler;
	ASSERT_EQ(state.playerOnMove, 0);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.playerOnMove, 1);
	LogicUtils::clearHookables();
}
TEST(PlayerPatchHandler, AddUnit)
{
	GameState state;
	state.players = { {3}, {3}, {3} };
	auto unit = std::make_shared<MockUnit>();
	Patch patch = PlayerPatch(1,unit);
	PlayerPatchHandler handler;
	ASSERT_EQ(state.players.at(1).units.size(), 0);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.players.at(1).units.size(), 1);
	ASSERT_EQ(state.players.at(1).units[0], unit);
	LogicUtils::clearHookables();
}

TEST(PlayerPatchHandler, AddResource)
{
	GameState state;
	state.players = { {3}, {3}, {3} };
	Patch patch = PlayerPatch(1,1,2);
	PlayerPatchHandler handler;
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 0);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 2);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 4);
}

TEST(PlayerPatchHandler, RemoveResources)
{
	GameState state;
	state.players = { {3}, {3}, {3} };
	state.players[1].acceptResources(1,4);
	Patch patch = PlayerPatch(1, 1, -2);
	PlayerPatchHandler handler;
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 4);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 2);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 0);
	LogicUtils::clearHookables();
}

TEST(PlayerPatchHandler, RemoveMoreResourcesThanHave)
{
	GameState state;
	state.players = { {3}, {3}, {3} };
	Patch patch = PlayerPatch(1, 1, -2);
	PlayerPatchHandler handler;
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 0);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.players.at(1).getResourceQuantity(1), 0);
	LogicUtils::clearHookables();
}

// RegisterHookablePatchHandler


TEST(RegisterHookablePatchHandler, RegisterHookable)
{
	GameState state;
	RegisterHookablePatchHandler handler;
	auto hookable = std::make_shared<MockHookable>();
	hookable->DelegateToFake();
	LogicUtils::addHookable(hookable);
	Patch patch = RegisterHookablePatch(hookable->getId());
	ASSERT_TRUE(state.registredHookables.empty());
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.registredHookables.size(), 1);
	ASSERT_NE(state.registredHookables.find(hookable->getId()), state.registredHookables.end());
	LogicUtils::clearHookables();
}

TEST(RegisterHookablePatchHandler, UnregisterHookable)
{
	GameState state;
	auto hookable = std::make_shared<MockHookable>();
	hookable->DelegateToFake();
	LogicUtils::addHookable(hookable);
	state.registredHookables.emplace(hookable->getId(), hookable);
	RegisterHookablePatchHandler handler;
	Patch patch = RegisterHookablePatch(hookable->getId(), false);
	ASSERT_EQ(state.registredHookables.size(), 1);
	handler.handlePatch(state, patch);
	ASSERT_TRUE(state.registredHookables.empty());
	LogicUtils::clearHookables();
}
// TilePatchHandler

TEST(TilePatchHandler, AddUnit)
{
	GameState state;
	state.map = createTestMap();
	auto unit = std::make_shared<MockUnit>();
	LogicUtils::addHookable(unit);
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 },unit->getId());
	ASSERT_FALSE(state.map[1][2].unit);
	handler.handlePatch(state, patch);
	ASSERT_TRUE(state.map[1][2].unit);
	ASSERT_EQ(state.map[1][2].unit, unit);
	LogicUtils::clearHookables();
}

TEST(TilePatchHandler, RemoveUnit)
{
	GameState state;
	state.map = createTestMap();
	state.map[1][2].unit = std::make_shared<MockUnit>();
	LogicUtils::addHookable(state.map[1][2].unit);
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 }, false, true);
	ASSERT_TRUE(state.map[1][2].unit);
	handler.handlePatch(state, patch);
	ASSERT_FALSE(state.map[1][2].unit);
	LogicUtils::clearHookables();
}

TEST(TilePatchHandler, AddObject)
{
	GameState state;
	state.map = createTestMap();
	auto object = std::make_shared<MockTileObject>();
	object->DelegateToFake();
	LogicUtils::addHookable(object);
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 }, object);
	ASSERT_FALSE(state.map[1][2].object);
	handler.handlePatch(state, patch);
	ASSERT_TRUE(state.map[1][2].object);
	ASSERT_EQ(state.map[1][2].object, object);
	LogicUtils::clearHookables();
}

TEST(TilePatchHandler, RemoveObject)
{
	GameState state;
	state.map = createTestMap();
	auto object = std::make_shared<MockTileObject>();
	object->DelegateToFake();
	LogicUtils::addHookable(object);
	state.map[1][2].object = object;
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 }, true, false);
	ASSERT_TRUE(state.map[1][2].object);
	handler.handlePatch(state, patch);
	ASSERT_FALSE(state.map[1][2].object);
	LogicUtils::clearHookables();
}

// UnitTilePatch 

TEST(UnitPatchHandler, AddMovementPoints)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, std::vector<std::string>(), hooks);
	LogicUtils::addHookable(unit);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit->getId(), 1);
	int mp = unit->movementPoints;
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, mp + 1);
	LogicUtils::clearHookables();
}

TEST(UnitPatchHandler, RemoveMovementPoints)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, std::vector<std::string>(), hooks);
	LogicUtils::addHookable(unit);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit->getId(), -1);
	int mp = unit->movementPoints;
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, mp - 1);
	LogicUtils::clearHookables();
}

TEST(UnitPatchHandler, TryAddMoreThanPossible)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, std::vector<std::string>(), hooks);
	LogicUtils::addHookable(unit);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit->getId(), 3*unit->baseMovementPoints);
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, 2*unit->baseMovementPoints);
	LogicUtils::clearHookables();
}

TEST(UnitPatchHandler, TryRemoveMoreThanPossible)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, std::vector<std::string>(), hooks);
	LogicUtils::addHookable(unit);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit->getId(), -2 * unit->movementPoints);
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, 0);
	LogicUtils::clearHookables();
}