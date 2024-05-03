cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
set(SFML_BUILD_AUDIO    OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS    OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_WINDOW    OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS    OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject src/main.cpp src/Gra.cpp)

target_link_libraries(CMakeSFMLProject PRIVATE sfml-network)
target_include_directories(CMakeSFMLProject PRIVATE include)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

