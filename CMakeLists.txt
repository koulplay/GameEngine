cmake_minimum_required(VERSION 3.12)

project(GameEngine CXX C)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(GameEngineCore)
add_subdirectory(GameEngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GameEngineEditor)