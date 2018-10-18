cmake_minimum_required(VERSION 3.12)
project(christmas_flatland)

set(CMAKE_CXX_STANDARD 11)

# Download and unpack catch at configure time
configure_file(CMakeLists.txt.in catch-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch-download)
if (result)
    message(FATAL_ERROR "CMake step for catch failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch-download)
if (result)
    message(FATAL_ERROR "Build step for catch failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add catch directly to our build
add_subdirectory(${CMAKE_BINARY_DIR}/catch-src
        ${CMAKE_BINARY_DIR}/catch-build
        EXCLUDE_FROM_ALL)

if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/single_include/catch2")
endif ()

# Now simply link against single_include/catch2 as needed.
include_directories(cmake-build-debug/catch-src/single_include/catch2)

add_executable(out main.cpp)
add_executable(test test.cpp)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY
)