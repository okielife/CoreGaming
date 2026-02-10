cmake_minimum_required(VERSION 3.22)

include(FetchContent)

cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(engine_tests test_camera.cpp)
target_link_libraries(engine_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(engine_tests)
