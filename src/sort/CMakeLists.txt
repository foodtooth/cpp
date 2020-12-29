project(sort)


add_library(sort)
target_sources(sort
        PRIVATE
        sort.cc)
target_include_directories(sort
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        )
target_compile_features(sort PUBLIC cxx_std_17)


if (BUILD_TESTING)
    add_executable(sort_test)
    target_sources(sort_test
            PRIVATE
            "${CMAKE_SOURCE_DIR}/test/main.test.cpp"
            sort.test.cc
            )
    target_include_directories(sort_test
            PRIVATE
            "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
            "$<INSTALL_INTERFACE:include>"
            )
    target_link_libraries(sort_test Catch2::Catch2)
    target_compile_features(sort_test PRIVATE cxx_std_17)
    catch_discover_tests(sort_test)
endif ()