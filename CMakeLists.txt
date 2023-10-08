cmake_minimum_required(VERSION 3.10)

project(MIPT_VM VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-std=c++17 -O2 -Wall -Wextra -Wpedantic)

add_library(mipt_vm
    STATIC
    runtime/runtime.cpp
    runtime/vm.cpp
    runtime/interpreter.cpp
    common/debug.cpp
)

target_include_directories(mipt_vm
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(benchmarks)
add_subdirectory(tests)
