cmake_minimum_required(VERSION 3.12)

project(GameEngineEditor CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(GameEngineEditor src/main.cpp)

target_link_libraries(GameEngineEditor GameEngineCore)

set_target_properties(GameEngineEditor PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DMAKE_BINARY_DIR}/bin/)