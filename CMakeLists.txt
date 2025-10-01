cmake_minimum_required(VERSION 3.10)
project(VastGpuFundsTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vastgpu_core 
    src/funds_calculator.cpp
    src/gpu_model.cpp
)
target_include_directories(vastgpu_core PUBLIC src)

add_executable(vastgpu_tracker src/main.cpp)
target_link_libraries(vastgpu_tracker vastgpu_core)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(boundary_tests tests/boundary.cpp)
target_link_libraries(boundary_tests vastgpu_core gtest_main)

add_executable(decision_table_tests tests/decision_table.cpp)
target_link_libraries(decision_table_tests vastgpu_core gtest_main)

include(GoogleTest)
gtest_discover_tests(boundary_tests)
gtest_discover_tests(decision_table_tests)

add_custom_target(run_all_tests 
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS boundary_tests decision_table_tests)


