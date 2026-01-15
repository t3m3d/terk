cmake_minimum_required(VERSION 3.21)
project(terk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Collect all source files recursively
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Qt6 discovery
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Executable
qt_add_executable(terk ${SOURCES})

# Include directories (modern style)
target_include_directories(terk PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/collect
    ${PROJECT_SOURCE_DIR}/include/render
    ${PROJECT_SOURCE_DIR}/include/platform
    ${PROJECT_SOURCE_DIR}/include/utils
    ${PROJECT_SOURCE_DIR}/include/branding
)

# Link Qt6
target_link_libraries(terk PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Windows-specific libraries
if (WIN32)
    target_link_libraries(terk PRIVATE
        Ws2_32
        Iphlpapi
        Kernel32
        User32
    )
endif()

# config + themes
install(FILES
    resources/config/terk.conf
    DESTINATION share/terk
)

install(DIRECTORY
    resources/themes
    DESTINATION share/terk
)