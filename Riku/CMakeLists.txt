cmake_minimum_required(VERSION 3.17)
SET(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
project(Riku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp -ljsoncpp")
set(CMAKE_CXX_STANDARD 17)

add_executable(Riku src/stb_image.cpp src/Texture.cpp src/Shader.cpp src/Mesh.cpp src/Model.cpp src/Object.cpp Riku/Riku.cpp src/Config.cpp)

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