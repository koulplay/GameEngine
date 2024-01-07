cmake_minimum_required(VERSION 3.12)

project(GameEngineCore CXX)
set(CMAKE_CXX_STANDARD 17)

set(ENGINE_PUBLIC_INCLUDES 
	includes/GameEngineCore/application.h
	includes/GameEngineCore/log.h
)

set(ENGINE_PRIVATE_SOURCES 
	src/GameEngineCore/application.cpp
)

add_library(GameEngineCore STATIC 
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)
	
target_include_directories(GameEngineCore PUBLIC includes)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(GameEngineCore PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(GameEngineCore PRIVATE spdlog)
