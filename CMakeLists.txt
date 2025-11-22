cmake_minimum_required(VERSION 3.28)
project(citybuilder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2  # or latest 3.x release
)

FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(citybuilder ${SOURCES})

target_link_libraries(citybuilder
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

target_include_directories(citybuilder
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)