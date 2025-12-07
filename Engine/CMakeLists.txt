file(GLOB_RECURSE xlEngineFiles
        CONFIGURE_DEPENDS
        "src/*cpp"
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

add_library(xlEngine ${xlEngineFiles})

target_link_libraries(xlEngine PUBLIC SFML::Graphics SFML::Window SFML::System)

target_include_directories(xlEngine PUBLIC
        $<INSTALL_INTERFACE:include>
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
