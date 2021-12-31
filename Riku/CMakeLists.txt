cmake_minimum_required(VERSION 3.17)
SET(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
project(Riku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp -ljsoncpp -Wall -Wextra -llua5.3")
set(CMAKE_CXX_STANDARD 20)

include_directories(Riku ${PROJECT_SOURCE_DIR}/lib "/usr/include/lua5.3")
include_directories(Riku ${PROJECT_SOURCE_DIR}/lib "/usr/include/x86_64-linux-gnu/cegui-0.8.7")
add_executable(Riku
	lib/hash-library/sha256.cpp
	lib/stb_image/stb_image.cpp
	src/GameLogic/Hooks/GUIDescription.cpp
	src/GameLogic/Hooks/LoadedHookable.cpp
	src/GameLogic/Tile/TileCost/Biome.cpp
	src/GameLogic/Tile/TileCost/Area.cpp
	src/GameLogic/Tile/TileCost/Ground.cpp
	src/GameLogic/Tile/Tile.cpp
	src/GameLogic/Tile/MapGenerator.cpp
	src/GameLogic/GameObject/SimpleTileObject.cpp
	src/GameLogic/GameObject/TileObjectDecoratorFactory.cpp
	src/GameLogic/GameObject/ResourceFactory.cpp
	src/GameLogic/GameObject/UseResourceOnBuild.cpp
	src/GameLogic/GameObject/RequireResources.cpp
	src/GameLogic/Assets/AssetHandler.cpp
	src/GameLogic/Assets/Asset.cpp
	src/GameLogic/Assets/AssetData.cpp
	src/GameLogic/StateUpdate/MoveFactory/ChoseGuiOptionMoveHandler.cpp
	src/GameLogic/StateUpdate/MoveFactory/MoveFactory.cpp
	src/GameLogic/StateUpdate/MoveFactory/TranslateUnitMoveHandler.cpp
	src/GameLogic/StateUpdate/MoveFactory/FinishGameMoveHandler.cpp
	src/GameLogic/StateUpdate/MoveFactory/TestMoveHandler.cpp
	src/GameLogic/StateUpdate/MoveFactory/BuildMoveHandler.cpp
	src/GameLogic/StateUpdate/PatchHandler/TilePatchHandler.cpp
	src/GameLogic/StateUpdate/PatchHandler/UnitPatchHandler.cpp
	src/GameLogic/StateUpdate/PatchHandler/PlayerPatchHandler.cpp
	src/GameLogic/StateUpdate/PatchHandler/PlayerOnMovePatchHandler.cpp
	src/GameLogic/StateUpdate/PatchHandler/RegisterHookablePatchHandler.cpp
	src/GameLogic/StateUpdate/Move/UseResources.cpp
	src/GameLogic/StateUpdate/Move/BuildTileObject.cpp
	src/GameLogic/StateUpdate/Move/CombinedMove.cpp
	src/GameLogic/StateUpdate/Move/FinishTurn.cpp
	src/GameLogic/StateUpdate/Move/TranslateUnit.cpp
	src/GameLogic/StateUpdate/Move/TestMove.cpp
	src/GameLogic/StateUpdate/Move/CreateUnit.cpp
	src/GameLogic/StateUpdate/Move/ExtractResources.cpp
	src/GameLogic/StateUpdate/StateUpdate.cpp
	src/GameLogic/FrontendCommunicator/Requests/Request.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/ShortestPathRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/PlayerResourcesRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/MapRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/PlayerUnitsRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/AssetHandlerRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/AvailableBuildingsRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/TileObjectGuiRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/PlayerOnMoveRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/Responses/MapResponse.cpp
	src/GameLogic/FrontendCommunicator/Responses/Response.cpp
	src/GameLogic/FrontendCommunicator/Responses/StringListResponse.cpp
	src/GameLogic/FrontendCommunicator/Responses/UnitListResponse.cpp
	src/GameLogic/FrontendCommunicator/Communicator.cpp
	src/GameLogic/Unit/Unit.cpp
	src/GameLogic/Unit/Hero.cpp
	src/GameLogic/Utils/LogicUtils.cpp
	src/GameLogic/Player/Player.cpp
	src/GameLogic/GameLogic.cpp
	src/GameLogic/LogicAssets.cpp
	src/Frontend/Asset/FAssetHandler.cpp
	src/Frontend/Asset/AssetModel.cpp
	src/Frontend/Asset/FAsset.cpp
	src/Frontend/Asset/AssetTexture.cpp
	src/Frontend/Window/Callbacks/MouseClickCallback.cpp
	src/Frontend/Window/Window.cpp
	src/Frontend/Window/Light.cpp
	src/Frontend/Window/Scene.cpp
	src/Frontend/FrontendState.cpp
	src/Frontend/Texture.cpp
	src/Frontend/Lang.cpp
	src/Frontend/Object.cpp
	src/Frontend/Model.cpp
	src/Frontend/GUIFactory.cpp
	src/Frontend/JsonUtil.cpp
	src/Frontend/Shader.cpp
	src/Frontend/Mesh.cpp
	src/Frontend/Config.cpp
	src/Frontend/GUIUpdate.cpp
	src/Frontend/Frontend.cpp
	src/Frontend/Transform.cpp
	src/Frontend/GUI.cpp
	src/Frontend/FrustumCulling.cpp
	src/Riku.cpp)

target_link_libraries(Riku dl)
target_link_libraries(Riku Xi)
target_link_libraries(Riku Xrandr)
target_link_libraries(Riku pthread)
target_link_libraries(Riku X11)
target_link_libraries(Riku GL)
target_link_libraries(Riku glfw)
target_link_libraries(Riku GLEW)
target_link_libraries(Riku assimp)
target_link_libraries(Riku jsoncpp)
target_link_libraries(Riku lua5.3)
target_link_libraries(Riku CEGUIBase-0)
target_link_libraries(Riku CEGUIOpenGLRenderer-0)
