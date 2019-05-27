add_executable(test_variance test_variance.cpp)
target_include_directories(test_variance PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../../include>)
target_link_libraries(test_variance gmock_main variance)
add_test(NAME test_variance COMMAND test_variance)
