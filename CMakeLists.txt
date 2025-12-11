cmake_minimum_required(VERSION 3.28)
project(clicker LANGUAGES CXX)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# Зависимости
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Clicker dependencies
file(GLOB_RECURSE CLICKER_SRC_FILES
        CONFIGURE_DEPENDS
        "clicker/src/*.cpp"
        "clicker/src/*.cxx"
        "clicker/src/*.cc"
)

add_executable(clicker ${CLICKER_SRC_FILES})

target_include_directories(clicker PUBLIC
        "clicker/include"
)

target_compile_definitions(clicker PUBLIC
        RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
)

target_compile_features(clicker PRIVATE cxx_std_20)

# Engine
add_subdirectory(Engine)
# Engine

target_compile_features(xlEngine PRIVATE cxx_std_20)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Engine")

    target_link_libraries(clicker PRIVATE xlEngine)
endif ()

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")

    add_library(test_dependencies INTERFACE)
    target_link_libraries(test_dependencies INTERFACE
            GTest::gtest
            GTest::gtest_main
            signal_bus
    )

    add_subdirectory(tests)
endif ()

enable_testing()