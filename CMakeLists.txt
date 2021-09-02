cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME GridSearchAlgorithm)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lSDL2_ttf")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(FindPkgConfig)

find_package(MathLibrary)
include_directories(${MATH_LIBRARY_INCLUDE_DIR})

include_directories(MAX_SDL_API)
add_executable(${PROJECT_NAME} main.cpp CSDL_Renderer.cpp CSDL_Controller.cpp CGrid.cpp CWorld.cpp GraphFunctions.cpp CSDL_Text.cpp SearchDataStructures.cpp)

target_link_libraries(${PROJECT_NAME} ${MATH_LIBRARY})

pkg_search_module(SDL2 REQUIRED sdl2)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_ttf)