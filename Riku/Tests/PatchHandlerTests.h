#pragma once
#include <gtest/gtest.h>
#include "../src/GameLogic/GameState.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/PlayerOnMovePatchHandler.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/PlayerPatchHandler.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/RegisterHookablePatchHandler.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/TilePatchHandler.h"
#include "Utils.h"
#include "../src/GameLogic/StateUpdate/PatchHandler/UnitPatchHandler.h"

TEST(PlayerOnMovePatchHandler, SetPlayerOnMove) 
{
	GameState state;
	state.players = { {3}, {3}, {3} };
	Patch patch(1);
	PlayerOnMovePatchHandler handler;
	ASSERT_EQ(state.playerOnMove, 0);
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.playerOnMove, 1);
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
}

// RegisterHookablePatchHandler


TEST(RegisterHookablePatchHandler, RegisterHookable)
{
	GameState state;
	RegisterHookablePatchHandler handler;
	auto hookable = std::make_shared<MockHookable>();
	Patch patch = RegisterHookablePatch(hookable);
	ASSERT_TRUE(state.registredHookables.empty());
	handler.handlePatch(state, patch);
	ASSERT_EQ(state.registredHookables.size(), 1);
	ASSERT_NE(state.registredHookables.find(hookable), state.registredHookables.end());
}

TEST(RegisterHookablePatchHandler, UnregisterHookable)
{
	GameState state;
	auto hookable = std::make_shared<MockHookable>();
	state.registredHookables.insert(hookable);
	RegisterHookablePatchHandler handler;
	Patch patch = RegisterHookablePatch(hookable, false);
	ASSERT_EQ(state.registredHookables.size(), 1);
	handler.handlePatch(state, patch);
	ASSERT_TRUE(state.registredHookables.empty());
}

// TilePatchHandler

TEST(TilePatchHandler, AddUnit)
{
	GameState state;
	state.map = createTestMap();
	auto unit = std::make_shared<MockUnit>();
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 },unit);
	ASSERT_FALSE(state.map[1][2].unit);
	handler.handlePatch(state, patch);
	ASSERT_TRUE(state.map[1][2].unit);
	ASSERT_EQ(state.map[1][2].unit, unit);
}

TEST(TilePatchHandler, RemoveUnit)
{
	GameState state;
	state.map = createTestMap();
	state.map[1][2].unit = std::make_shared<MockUnit>();
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 }, false, true);
	ASSERT_TRUE(state.map[1][2].unit);
	handler.handlePatch(state, patch);
	ASSERT_FALSE(state.map[1][2].unit);
}

TEST(TilePatchHandler, AddObject)
{
	GameState state;
	state.map = createTestMap();
	auto object = std::make_shared<MockTileObject>();
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 }, object);
	ASSERT_FALSE(state.map[1][2].object);
	handler.handlePatch(state, patch);
	ASSERT_TRUE(state.map[1][2].object);
	ASSERT_EQ(state.map[1][2].object, object);
}

TEST(TilePatchHandler, RemoveObject)
{
	GameState state;
	state.map = createTestMap();
	state.map[1][2].object = std::make_shared<MockTileObject>();
	TilePatchHandler handler;
	Patch patch = TilePatch({ 1,2 }, true, false);
	ASSERT_TRUE(state.map[1][2].object);
	handler.handlePatch(state, patch);
	ASSERT_FALSE(state.map[1][2].object);
}

// UnitTilePatch 

TEST(UnitPatchHandler, AddMovementPoints)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, hooks);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit, 1);
	int mp = unit->movementPoints;
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, mp + 1);
}

TEST(UnitPatchHandler, RemoveMovementPoints)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, hooks);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit, -1);
	int mp = unit->movementPoints;
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, mp - 1);
}

TEST(UnitPatchHandler, TryAddMoreThanPossible)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, hooks);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit, 3*unit->baseMovementPoints);
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, 2*unit->baseMovementPoints);
}

TEST(UnitPatchHandler, TryRemoveMoreThanPossible)
{
	GameState state;
	auto unit = std::make_shared<Unit>("", "", 0, 100, hooks);
	UnitPatchHandler handler;
	Patch patch = UnitPatch(unit, -2 * unit->movementPoints);
	handler.handlePatch(state, patch);
	ASSERT_EQ(unit->movementPoints, 0);
}