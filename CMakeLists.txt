cmake_minimum_required(VERSION 3.16)
project(terk C CXX)

# C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Collect all source files recursively
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)


# Include directories (mirrors your modular structure)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/collect
    ${PROJECT_SOURCE_DIR}/include/render
    ${PROJECT_SOURCE_DIR}/include/platform
    ${PROJECT_SOURCE_DIR}/include/utils
    ${PROJECT_SOURCE_DIR}/include/branding
)

# Executable
add_executable(terk ${SOURCES})

# Windows-specific libraries
if (WIN32)
    target_link_libraries(terk
        Ws2_32
        Iphlpapi
        Kernel32
        User32
    )
endif()

install(FILES
    resources/config/terk.conf
    DESTINATION share/terk
)

install(DIRECTORY
    resources/themes
    DESTINATION share/terk
)