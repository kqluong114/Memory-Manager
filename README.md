
# Memory Manager

A simple **Memory Manager** implementation in C++ that simulates virtual memory concepts such as caching, eviction, and disk I/O management.  
This project was created as part of coursework to better understand operating systems and memory handling.

## Features

- Manages memory pages between **disk** and **cache**
- Implements **caching** to minimize reads/writes
- Supports **page eviction** policies
- Written in **C++** with a focus on efficiency and clarity

## Project Structure

```
Memory-Manager/
├── src/          # Source files
├── include/      # Header files
├── tests/        # Test cases
└── README.md     # Documentation (this file)
```

## Getting Started

### Prerequisites
- A C++ compiler (g++, clang, or MSVC)
- CMake (optional, if you want to build with CMake)

### Compilation

Using g++:
```bash
g++ -std=c++17 -o memory_manager src/*.cpp
```

Using CMake:
```bash
mkdir build && cd build
cmake ..
make
```

### Running
```bash
./memory_manager
```
