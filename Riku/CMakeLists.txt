cmake_minimum_required(VERSION 3.17)
SET(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
project(Riku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp -ljsoncpp -Wall -Wextra -llua5.3")
set(CMAKE_CXX_STANDARD 20)

include_directories(Riku ${PROJECT_SOURCE_DIR}/lib "/usr/include/lua5.3")
include_directories(Riku ${PROJECT_SOURCE_DIR}/lib "/usr/include/x86_64-linux-gnu/cegui-0.8.7")
add_executable(Riku
        lib/hash-library/sha256.cpp
        src/GameLogic/Tile/TileCost/Biome.cpp
	src/GameLogic/Tile/TileCost/Area.cpp
	src/GameLogic/Tile/TileCost/Ground.cpp
	src/GameLogic/Tile/Tile.cpp
	src/GameLogic/GameObject/SimpleTileObject.cpp
	src/GameLogic/GameObject/ResourceFactory.cpp
	src/GameLogic/Assets/Asset.cpp
	src/GameLogic/StateUpdate/PatchHandler/PlayerPatchHandler.cpp
	src/GameLogic/StateUpdate/Move/ExtractResources.cpp
	src/GameLogic/StateUpdate/StateUpdate.cpp
	src/GameLogic/FrontendCommunicator/Requests/Request.cpp
	src/GameLogic/FrontendCommunicator/RequestHandlers/MapRequestHandler.cpp
	src/GameLogic/FrontendCommunicator/Responses/MapResponse.cpp
	src/GameLogic/FrontendCommunicator/Responses/Response.cpp
	src/GameLogic/FrontendCommunicator/Communicator.cpp
	src/GameLogic/Player/Player.cpp
	src/GameLogic/GameLogic.cpp
	src/GameLogic/LogicAssets.cpp
	src/Frontend/Texture.cpp
	src/Frontend/stb_image.cpp
	src/Frontend/Object.cpp
	src/Frontend/Model.cpp
	src/Frontend/Shader.cpp
	src/Frontend/Mesh.cpp
	src/Frontend/Config.cpp
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
