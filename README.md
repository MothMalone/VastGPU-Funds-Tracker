# VastGPU Funds Tracker

A command-line calculator for tracking and estimating GPU instance costs on cloud platforms.

## Requirements
- C++ compiler supporting C++17 or newer (g++, clang, MSVC, etc.)
- CMake 3.10 or newer (for CMake build only)

## Project Setup

### Building with CMake

1. Create a build directory:
```bash
mkdir build && cd build
```

2. Configure and build:
```bash
cmake ..
make
```

3. Run the program:
```bash
./vastgpu_tracker
```

### Running Tests

After building the project with CMake, you can run the tests:

```bash
# Run all tests
ctest

# Run specific test
./boundary_tests
./decision_table_tests
```

### Direct Compilation

You can also compile directly using g++:
```bash
g++ -std=c++17 src/main.cpp src/gpu_model.cpp src/funds_calculator.cpp -I src -o vastgpu_tracker
```




