cmake_minimum_required(VERSION 3.12)

project(GameEngineEditor CXX C)
set(CMAKE_CXX_STANDARD 17)

add_executable(GameEngineEditor src/main.cpp)

target_link_libraries(GameEngineEditor GameEngineCore ImGui glm)