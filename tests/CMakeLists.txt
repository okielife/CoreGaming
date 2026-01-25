cmake_minimum_required(VERSION 3.22)

include(FetchContent)

cmake_policy(SET CMP0135 NEW)

# 1. Declare the googletest dependency
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
)

# 2. Make the googletest targets available
# This step fetches the content and adds the googletest subdirectory
FetchContent_MakeAvailable(googletest)

# Prevent GoogleTest from overriding our compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(engine_tests
        test_camera.cpp
)

target_link_libraries(engine_tests
        PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(engine_tests)
