cmake_minimum_required(VERSION 3.28)

project(astrovector VERSION 1.0.0)



include(FetchContent) # This was added to use CMake's FetchContent module

add_executable(astrovector main.cpp)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    sgp4
    GIT_REPOSITORY https://github.com/dnwrnr/sgp4.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)

FetchContent_Declare( # This was added to fetch SFML from GitHub
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(sgp4)

target_sources(astrovector
    PRIVATE
     main.cpp
)

target_compile_features(astrovector PRIVATE cxx_std_20)

target_link_libraries(astrovector PRIVATE
    SFML::Graphics
    SGP4::sgp4
)