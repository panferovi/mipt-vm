include(GoogleTest)

find_package(GTest REQUIRED)

add_executable(mipt_vm_unit_tests
    mipt_vm.cpp
)

target_link_libraries(mipt_vm_unit_tests
    PUBLIC mipt_vm
    PUBLIC stdlib
    PUBLIC GTest::gtest_main
)

gtest_discover_tests(mipt_vm_unit_tests)
