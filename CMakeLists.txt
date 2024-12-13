cmake_minimum_required(VERSION 3.16)

project(cpp
        LANGUAGES CXX)

add_compile_options(-Wall -Wextra -pedantic -Werror
        "$<$<CONFIG:Debug>:-O0;-g3;-ggdb>"
        "$<$<CONFIG:Release>:-O3>"
        )

if (BUILD_TESTING)
    find_package(Catch2 REQUIRED)
    include(CTest)
    include(Catch)
endif ()

# Add other lib directories here
add_subdirectory(src/thread_pool)
add_subdirectory(src/union_find)
add_subdirectory(src/sort)
add_subdirectory(src/dio)
add_subdirectory(src/common)
add_subdirectory(src/state_machine)