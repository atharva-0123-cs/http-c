# ======================================================
# Basic project setup
# ======================================================
cmake_minimum_required(VERSION 3.15)
project(web_server VERSION 1.0 LANGUAGES C)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Export compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

# ======================================================
# Source files
# ======================================================
set(SOURCES
    src/main.c
    # src/handle_client.c
    src/network.c
    # src/sig_utils.c
)

# Main executable
add_executable(web_server ${SOURCES})
target_include_directories(web_server PRIVATE ${CMAKE_SOURCE_DIR}/include)

# POSIX macros
add_compile_definitions(_POSIX_C_SOURCE=200112L)

# Warnings
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(web_server PRIVATE -Wall -Wextra -Wpedantic -g)
endif()

# ======================================================
# CMocka Unit Tests
# ======================================================
# Find CMocka
find_package(PkgConfig REQUIRED)
pkg_check_modules(CMOCKA REQUIRED cmocka)

# Test executable
add_executable(test_network tests/test_network.c src/network.c)
target_include_directories(test_network PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMOCKA_INCLUDE_DIRS}
)
target_link_libraries(test_network ${CMOCKA_LIBRARIES})

# Register test with CTest
enable_testing()
add_test(NAME NetworkTests COMMAND test_network)
