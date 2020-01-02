project(thread_pool)

get_property(ROOT GLOBAL PROPERTY root)

add_library(thread_pool thread_pool.cc)
target_include_directories(thread_pool
        PUBLIC
        $<BUILD_INTERFACE:${ROOT}/include>
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()
