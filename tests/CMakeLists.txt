message(STATUS "Tests are enabled (PULSO_BUILD_TESTS=ON)")

# Descargar e integrar Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Evitar que GTest sobreescriba flags del compilador
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Target de tests
add_executable(test_pulso
    automatizados/unit/test_monitor_config.cpp
)

target_include_directories(test_pulso PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(test_pulso
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_pulso)
