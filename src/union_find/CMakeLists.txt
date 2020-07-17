project(union_find)

add_library(union_find)
target_sources(union_find
        PRIVATE
        union_find.cc)
target_include_directories(union_find
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        )
target_compile_features(union_find PUBLIC cxx_std_17)
target_compile_options(union_find
        PUBLIC
        "$<$<CONFIG:Debug>:>"
        )

add_executable(union_find_example)
target_sources(union_find_example
        PRIVATE
        union_find.example.cc)
target_include_directories(union_find_example
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )
target_link_libraries(union_find_example PRIVATE union_find)
target_compile_features(union_find_example PRIVATE cxx_std_17)