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

function(filter_items aItems aRegEx)
    foreach(item ${${aItems}})
        if("${item}" MATCHES ${aRegEx})
            list(REMOVE_ITEM ${aItems} ${item})
        endif("${item}" MATCHES ${aRegEx})
    endforeach(item)
    set(${aItems} ${${aItems}} PARENT_SCOPE)
endfunction (filter_items)

file(GLOB_RECURSE MIPT_VM_FILES *.cpp *.h)
filter_items(MIPT_VM_FILES "CMakeFiles/*")

find_program(CLANG_FORMAT "clang-format-14" REQUIRED)

add_custom_target(format
    COMMAND clang-format-14
    -i
    -style=file
    ${MIPT_VM_FILES}
)
