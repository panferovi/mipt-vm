add_library(stdlib
    STATIC
    io.cpp
    math.cpp
)

target_include_directories(stdlib
    PUBLIC ${SRC_ROOT_DIR}
)
