
cmake_minimum_required(VERSION 3.14)
project(EventBus C CXX)
find_package(Threads REQUIRED)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  EventBus0_test
  EventBus0_test.cc
)
add_executable(
  EventBus1_test
  EventBus1_test.cc
)
add_executable(
  EventBus2_test
  EventBus2_test.cc
)
target_link_libraries(
  EventBus0_test
  gtest_main
)
target_link_libraries(
  EventBus1_test
  gtest_main
)
target_link_libraries(
  EventBus2_test
  gtest_main
)

include(GoogleTest)

gtest_discover_tests(EventBus0_test)
gtest_discover_tests(EventBus1_test)
gtest_discover_tests(EventBus2_test)
