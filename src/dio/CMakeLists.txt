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

add_executable(dio_client)
target_sources(dio_client
        PRIVATE
        dio.client.cc)
target_include_directories(dio_client
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )
target_link_libraries(dio_client PRIVATE dio)
target_compile_features(dio_client PRIVATE cxx_std_17)

add_executable(dio_server)
target_sources(dio_server
        PRIVATE
        dio.server.cc)
target_include_directories(dio_server
        PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )
target_link_libraries(dio_server PRIVATE dio)
target_compile_features(dio_server PRIVATE cxx_std_17)