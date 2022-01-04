#pragma once
#include <gtest/gtest.h>
#include "../src/GameLogic/Assets/Asset.h"

TEST(LuaAssets, SimpleAssetReading) 
{
	std::string path = "testAssets/basicLuaTest";
	std::string filename = "script.lua";
	auto asset = logic::Asset(path, filename);
	ASSERT_EQ(asset.getType(), "test");
	ASSERT_EQ(asset.getName(), "testName");
}

TEST(LuaAssets, ReadingVariable)
{
	std::string path = "testAssets/basicLuaTest";
	std::string filename = "script.lua";
	auto asset = logic::Asset(path, filename);
	ASSERT_EQ(asset.getByKey("test_variable").asInt(), 10);
}

TEST(LuaAssets, ReadingFunction)
{
	std::string path = "testAssets/functionAsset";
	std::string filename = "script.lua";
	auto asset = logic::Asset(path, filename);
	ASSERT_TRUE(asset.hasFunction("onTestFunction"));
	ASSERT_NO_THROW((int)asset.getFunction("onTestFunction")());
	ASSERT_EQ((int)asset.getFunction("onTestFunction")(), 10);
}