cmake_minimum_required(VERSION 3.28)

project(astrovector VERSION 1.0.0)

include(FetchContent) # This was added to use CMake's FetchContent module

add_executable(astrovector main.cpp  )

FetchContent_Declare( # This was added to fetch SFML from GitHub
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SFML)

target_sources(astrovector
    PRIVATE
     main.cpp
)

target_compile_features(astrovector PRIVATE cxx_std_20)

target_link_libraries(astrovector PRIVATE
    SFML::Graphics
)