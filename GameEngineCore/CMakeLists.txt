cmake_minimum_required(VERSION 3.12)

project(GameEngineCore CXX C)
set(CMAKE_CXX_STANDARD 17)

set(ENGINE_PUBLIC_INCLUDES 
	includes/GameEngineCore/application.h
	includes/GameEngineCore/log.h
	includes/GameEngineCore/event.h
	includes/GameEngineCore/mouseEvent.h
	includes/GameEngineCore/windowEvent.h
	includes/GameEngineCore/keyEvent.h
	includes/GameEngineCore/camera.h
	includes/GameEngineCore/keys.h
	includes/GameEngineCore/input.h
	includes/GameEngineCore/texture.h
	includes/GameEngineCore/mash.h
)

set(ENGINE_PRIVATE_INCLUDES
	src/GameEngineCore/window.h
	src/GameEngineCore/Rendering/OpenGL/rendererOpenGL.h
	src/GameEngineCore/Rendering/OpenGL/shaderProgram.h
	src/GameEngineCore/Rendering/OpenGL/vertexBuffer.h
	src/GameEngineCore/Rendering/OpenGL/vertexArray.h
	src/GameEngineCore/Rendering/OpenGL/indexBuffer.h
	src/GameEngineCore/Rendering/OpenGL/rendererOpenGL.h
	src/GameEngineCore/Modules/UIModule.h
)

set(ENGINE_PRIVATE_SOURCES 
	src/GameEngineCore/application.cpp
	src/GameEngineCore/window.cpp
	src/GameEngineCore/camera.cpp
	src/GameEngineCore/Rendering/OpenGL/rendererOpenGL.cpp
	src/GameEngineCore/Rendering/OpenGL/shaderProgram.cpp
	src/GameEngineCore/Rendering/OpenGL/vertexBuffer.cpp
	src/GameEngineCore/Rendering/OpenGL/vertexArray.cpp
	src/GameEngineCore/Rendering/OpenGL/indexBuffer.cpp
	src/GameEngineCore/Rendering/OpenGL/rendererOpenGL.cpp
	src/GameEngineCore/Modules/UIModule.cpp
	src/GameEngineCore/input.cpp
	src/GameEngineCore/texture.cpp
	src/GameEngineCore/mash.cpp
)

set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

add_library(GameEngineCore STATIC 
	${ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
	${ENGINE_ALL_SOURCES}
)
	
target_include_directories(GameEngineCore PUBLIC includes)
target_include_directories(GameEngineCore PRIVATE src)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(GameEngineCore PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(GameEngineCore PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(GameEngineCore PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(GameEngineCore PRIVATE glm)

add_subdirectory(../external/SOIL2 ${CMAKE_CURRENT_BINARY_DIR}/SOIL2)
target_link_libraries(GameEngineCore PRIVATE soil2)

add_subdirectory(../external/assimp ${CMAKE_CURRENT_BINARY_DIR}/assimp)
target_link_libraries(GameEngineCore PRIVATE assimp)

set(IMGUI_INCLUDES
	../external/imgui/imgui.h 
	../external/imgui/backends/imgui_impl_glfw.h 
	../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES 
	../external/imgui/imgui.cpp 
	../external/imgui/backends/imgui_impl_glfw.cpp 
	../external/imgui/backends/imgui_impl_opengl3.cpp
	../external/imgui/imgui_draw.cpp
	../external/imgui/imgui_demo.cpp
	../external/imgui/imgui_tables.cpp
	../external/imgui/imgui_widgets.cpp
)

add_library(ImGui STATIC 
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)

target_link_libraries(ImGui PRIVATE glad glfw) 

target_link_libraries(GameEngineCore PRIVATE ImGui) 