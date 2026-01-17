cmake_minimum_required(VERSION 3.31)
project(CoreGaming)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

option(BUILD_TESTING "Turn this ON to enable testing" ON)
if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif ()
