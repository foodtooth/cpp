project(graph)

add_executable(example example.cc)

target_include_directories(example
        PRIVATE ${CMAKE_CURRENT_LIST_DIR})