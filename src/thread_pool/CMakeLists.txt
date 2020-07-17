project(thread_pool)

find_package(Threads REQUIRED)

add_library(thread_pool)
target_sources(thread_pool
        PRIVATE
        thread_pool.cc)
target_include_directories(thread_pool
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        )
target_link_libraries(thread_pool PRIVATE Threads::Threads)
target_compile_features(thread_pool PUBLIC cxx_std_17)
target_compile_options(thread_pool
        PUBLIC
        "$<$<CONFIG:Debug>:>"
        )

add_executable(thread_pool_example)
target_sources(thread_pool_example
        PRIVATE
        thread_pool.example.cc)
target_include_directories(thread_pool_example
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )
target_link_libraries(thread_pool_example PRIVATE thread_pool)
target_compile_features(thread_pool_example PRIVATE cxx_std_17)

if (BUILD_TESTING)
    add_executable(thread_pool_test)
    target_sources(thread_pool_test
            PRIVATE
            "${CMAKE_SOURCE_DIR}/test/main.test.cpp"
            thread_pool.test.cc
            )
    target_include_directories(thread_pool_test
            PRIVATE
            "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
            "$<INSTALL_INTERFACE:include>"
            )
    target_link_libraries(thread_pool_test Catch2::Catch2)
    target_compile_features(thread_pool_test PRIVATE cxx_std_17)
    catch_discover_tests(thread_pool_test)
endif ()
