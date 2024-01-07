cmake_minimum_required(VERSION 3.12)

project(GameEngineCore CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(GameEngineCore STATIC 
	src/GameEngineCore/Utils/test.cpp
	includes/GameEngineCore/Utils/test.h)
	
target_include_directories(GameEngineCore PUBLIC includes)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(GameEngineCore PRIVATE glfw)

