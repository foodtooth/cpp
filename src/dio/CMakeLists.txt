project(dio)

add_library(dio)
target_sources(dio
        PRIVATE
        dio.cc)
target_include_directories(dio
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        )
target_compile_features(dio PUBLIC cxx_std_17)

add_executable(dio_example)
target_sources(dio_example
        PRIVATE
        dio.example.cc)
target_include_directories(dio_example
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )
target_link_libraries(dio_example PRIVATE dio)
target_compile_features(dio_example PRIVATE cxx_std_17)