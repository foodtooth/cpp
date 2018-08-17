cmake_minimum_required(VERSION 3.5.1)

project(cpp
    VERSION 1.0.0.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make our config header included
configure_file(
    "${PROJECT_SOURCE_DIR}/cppConfig.h.in"
    "${PROJECT_BINARY_DIR}/cppConfig.h")

# Add project build dir to include path
include_directories("${PROJECT_BINARY_DIR}")

# Download and unpack gtest at configure time
configure_file(lib/gtest/CMakeLists.txt.in gtest/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" . RESULT_VARIABLE result WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/gtest")
if (result)
    message(FATAL_ERROR "CMake step for gtest failed: ${result}")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build . RESULT_VARIABLE result WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/gtest")
if (result)
    message(FATAL_ERROR "Build step for gtest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add gtest to our build, including gtest, gtest_main, gmock, gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/gtest-src" "${CMAKE_BINARY_DIR}/gtest-build")

enable_testing()

add_subdirectory(src/variance)
