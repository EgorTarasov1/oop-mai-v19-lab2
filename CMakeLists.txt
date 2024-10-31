cmake_minimum_required(VERSION 3.10)
project(l2)

include_directories(include)

add_executable(main_l2 l2.cpp Three.cpp)

add_executable(test_l2 test.cpp Three.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(
  test_l2
  GTest::gtest_main
)

include(GoogleTest)

add_test(NAME test_l2 COMMAND test_l2)