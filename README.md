# VastGPU Funds Tracker

A command-line calculator for tracking and estimating GPU instance costs on cloud platforms.


## Requirements
- C++ compiler supporting C++11 or newer (g++, clang, MSVC, etc.)
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
./bin/vastgpu_tracker
```

Direct Compilation
You can also compile directly using g++:
```bash
g++ -std=c++11 src/main.cpp src/gpu_model.cpp src/funds_calculator.cpp -I src -o vastgpu_tracker
```




