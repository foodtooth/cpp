project(common)

add_executable(singleton_example)
target_sources(singleton_example
        PRIVATE
        singleton.example.cc)
target_include_directories(singleton_example
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )
target_compile_features(singleton_example PRIVATE cxx_std_17)