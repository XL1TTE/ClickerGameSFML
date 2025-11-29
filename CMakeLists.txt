cmake_minimum_required(VERSION 3.28)

project(clicker LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE CLICKER_SRC_FILE CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/clicker/src/*")
#file(GLOB_RECURSE CLICKER_SRC_FILE CONFIGURE_DEPENDS "./src/clicker/*")

add_executable(clicker ${CLICKER_SRC_FILE})

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_include_directories(clicker PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/clicker/include/")

target_compile_features(clicker PRIVATE cxx_std_20)
target_link_libraries(clicker PRIVATE SFML::Graphics)

