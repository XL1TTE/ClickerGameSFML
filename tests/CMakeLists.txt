# Тестовое приложение
file(GLOB_RECURSE SIGNAL_BUS_TESTS_FILES
        CONFIGURE_DEPENDS
        "SignalBusTests.cpp"
)

add_executable(signal_bus_tests ${SIGNAL_BUS_TESTS_FILES})

target_include_directories(signal_bus_tests PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../clicker/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../clicker/src"
)

target_compile_definitions(signal_bus_tests PUBLIC
        RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../resources/"
)

target_compile_features(signal_bus_tests PRIVATE cxx_std_20)

# Линковка
target_link_libraries(signal_bus_tests
        PRIVATE
        test_dependencies
)

include(GoogleTest)
gtest_discover_tests(signal_bus_tests)