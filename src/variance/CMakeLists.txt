project(variance)

add_library(variance variance.cpp)
target_include_directories(variance
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../include>
        )

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()
