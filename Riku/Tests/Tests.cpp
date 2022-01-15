#include <iostream>
#include <gtest/gtest.h>
#include "PlayerTests.h"
#include "TileTest.h"
#include "PatchesTests.h"
#include "PatchHandlerTests.h"
#include "LuaAssetsTests.h"
#include "LogicAssetTests.h"
#include "FrontendLogicIntegration.h"
#include "FrontendMiniGameIntegration.h"

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}