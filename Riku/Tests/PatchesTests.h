#pragma once
#include <gtest/gtest.h>
#include "../src/GameLogic/StateUpdate/Patch/Patch.h"
#include "Mocks.h"

//PlayerPatch

TEST(PlayerPatch, AddResourceQuantietes) {
	PlayerPatch patch1(1, 0, 1);
	PlayerPatch patch2(1, 0, 2);
	patch1 += patch2;
	ASSERT_EQ(patch1.resourceChanges.size(), 1);
	ASSERT_EQ(patch1.resourceChanges[0], 3);
}

TEST(PlayerPatch, AddDiferentResource) {
	PlayerPatch patch1(1, 1, 2);
	PlayerPatch patch2(1, 0, 1);
	patch1 += patch2;
	ASSERT_EQ(patch1.resourceChanges.size(), 2);
	ASSERT_EQ(patch1.resourceChanges[0], 1);
	ASSERT_EQ(patch1.resourceChanges[1], 2);
}

TEST(PlayerPatch, AddUnit) {
	auto u1 = std::make_shared<MockUnit>();
	auto u2 = std::make_shared<MockUnit>();
	PlayerPatch patch1(1, u1);
	PlayerPatch patch2(1, u2);
	ASSERT_EQ(patch1.addedUnits.size(), 1);
	patch1 += patch2;
	ASSERT_EQ(patch1.addedUnits.size(), 2);
	ASSERT_EQ(patch1.addedUnits[0], u1);
	ASSERT_EQ(patch1.addedUnits[1], u2);
}

//TilePatch

TEST(TilePatch, AddUnit) {
	auto u1 = "unit1_id";
	auto u2 = "unit2_id";
	TilePatch patch1({ 1,2 }, u1);
	TilePatch patch2({ 1,2 }, u2);
	ASSERT_EQ(patch1.unit, u1);
	patch1 += patch2;
	ASSERT_EQ(patch1.unit, u2);
}

TEST(TilePatch, RemoveUnit) {
	auto unit = "unit1_id";
	TilePatch patch1({ 1,2 }, unit);
	TilePatch patch2({ 1,2 }, false, true);
	ASSERT_EQ(patch1.unit, unit);
	patch1 += patch2;
	ASSERT_EQ(patch1.unit, "");
}

TEST(TilePatch, AddTileObject) {
	auto object1 = std::make_shared<MockTileObject>();
	auto object2 = std::make_shared<MockTileObject>();
	TilePatch patch1({ 1,2 }, object1);
	TilePatch patch2({ 1,2 }, object2);
	ASSERT_EQ(patch1.object, object1);
	patch1 += patch2;
	ASSERT_EQ(patch1.object, object2);
}

TEST(TilePatch, RemoveTileObject) {
	auto object = std::make_shared<MockTileObject>();
	TilePatch patch1({ 1,2 }, object);
	TilePatch patch2({ 1,2 }, true, false);
	ASSERT_EQ(patch1.object, object);
	patch1 += patch2;
	ASSERT_FALSE(patch1.object);
}

// RegisterHookablePatch

TEST(RegisterHookablePatch, AddAndRemoveHookable) {
	auto hookable = "hookable1_id";
	RegisterHookablePatch patch1( hookable );
	RegisterHookablePatch patch2( hookable, false );
	ASSERT_TRUE(patch1.add);
	patch1 += patch2;
	ASSERT_FALSE(patch1.add);
}

// Patch

TEST(Patch, AddSimilarPlayerPatches)
{
	Patch patch1(PlayerPatch(1, 0, 1));
	Patch patch2(PlayerPatch(1, 0, 1));
	Patch sum = patch1 + patch2;
	ASSERT_EQ(sum.playerPatches.size(), 1);
	ASSERT_EQ(sum.playerPatches.at(1).resourceChanges.size(), 1);
	ASSERT_EQ(sum.playerPatches.at(1).resourceChanges[0], 2);
}

TEST(Patch, AddDiferentPlayerPatches)
{
	Patch patch1(PlayerPatch(0, 0, 1));
	Patch patch2(PlayerPatch(1, 0, 1));
	Patch sum = patch1 + patch2;
	ASSERT_EQ(sum.playerPatches.size(), 2);
	ASSERT_EQ(sum.playerPatches.at(0).resourceChanges.size(), 1);
	ASSERT_EQ(sum.playerPatches.at(0).resourceChanges[0], 1);
}

TEST(Patch, AddSimilarTilePatches)
{
	auto u1 = "unit1_id";
	auto u2 = "unit2_id";
	Patch patch1(TilePatch({ 1,2 }, u1));
	Patch patch2(TilePatch({ 1,2 }, u2));
	Patch sum = patch1 + patch2;
	ASSERT_EQ(sum.tilePatches.size(), 1);
	ASSERT_EQ(sum.tilePatches.at(std::make_pair(1,2)).unit, u2);
}

TEST(Patch, AddDiferentTilePatches)
{
	auto u1 = "unit1_id";
	auto u2 = "unit2_id";
	Patch patch1(TilePatch({ 0,2 }, u1));
	Patch patch2(TilePatch({ 1,2 }, u2));
	Patch sum = patch1 + patch2;
	ASSERT_EQ(sum.tilePatches.size(), 2);
	ASSERT_NE(sum.tilePatches.find(std::make_pair(0, 2)), sum.tilePatches.end());
	ASSERT_NE(sum.tilePatches.find(std::make_pair(1, 2)), sum.tilePatches.end());
}

TEST(Patch, AddSimilarHookablePatches)
{
	auto hookable = "hookable1_id";
	Patch patch1(RegisterHookablePatch(hookable, true));
	Patch patch2(RegisterHookablePatch(hookable, false));
	Patch sum = patch1 + patch2;
	ASSERT_EQ(sum.registerHookablePatches.size(), 1);
}

TEST(Patch, AddDiferentHookablePatches)
{
	auto h1 = "hookable1_id";
	auto h2 = "hookable2_id";
	Patch patch1( RegisterHookablePatch( h1, true ));
	Patch patch2(RegisterHookablePatch( h2, true ));
	Patch sum = patch1 + patch2;
	ASSERT_EQ(sum.registerHookablePatches.size(), 2);
	ASSERT_NE(sum.registerHookablePatches.find(h1), sum.registerHookablePatches.end());
	ASSERT_NE(sum.registerHookablePatches.find(h2), sum.registerHookablePatches.end());
}