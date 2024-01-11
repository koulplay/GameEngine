cmake_minimum_required(VERSION 3.12)

project(GameEngineCore CXX)
set(CMAKE_CXX_STANDARD 17)

set(ENGINE_PUBLIC_INCLUDES 
	includes/GameEngineCore/application.h
	includes/GameEngineCore/log.h
	includes/GameEngineCore/event.h
	includes/GameEngineCore/mouseEvent.h
	includes/GameEngineCore/windowEvent.h
	includes/GameEngineCore/keyEvent.h
)

set(ENGINE_PRIVATE_INCLUDES
	src/GameEngineCore/window.h
)

set(ENGINE_PRIVATE_SOURCES 
	src/GameEngineCore/application.cpp
	src/GameEngineCore/window.cpp
)

add_library(GameEngineCore STATIC 
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)
	
target_include_directories(GameEngineCore PUBLIC includes)
target_include_directories(GameEngineCore PRIVATE src)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(GameEngineCore PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(GameEngineCore PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(GameEngineCore PRIVATE glad)
