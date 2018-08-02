add_executable(variance_test variance_test.cpp)
target_include_directories(variance_test PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../../include>)
target_link_libraries(variance_test gtest_main variance)
add_test(NAME variance_test COMMAND variance_test)
