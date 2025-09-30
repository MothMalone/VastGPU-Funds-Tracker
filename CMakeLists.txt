cmake_minimum_required(VERSION 3.10)
project(VastGpuFundsTracker)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp
    src/funds_calculator.cpp
    src/gpu_model.cpp
)

include_directories(src)

add_executable(vastgpu_tracker ${SOURCES})

set_target_properties(vastgpu_tracker PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS vastgpu_tracker DESTINATION bin)
