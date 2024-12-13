project(state_machine)

add_library(state_machine)
target_sources(state_machine
        PRIVATE
        state_machine.cc)
target_include_directories(state_machine
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        )
target_compile_features(state_machine PUBLIC cxx_std_17)
target_compile_options(state_machine
        PUBLIC
        "$<$<CONFIG:Debug>:>"
        )

add_executable(state_machine_example)
target_sources(state_machine_example
        PRIVATE
        state_machine.example.cc)
target_include_directories(state_machine_example
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )
target_link_libraries(state_machine_example PRIVATE state_machine)
target_compile_features(state_machine_example PRIVATE cxx_std_17)