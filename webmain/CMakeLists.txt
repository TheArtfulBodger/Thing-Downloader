cmake_minimum_required(VERSION 3.10)

include_directories(
    ${CMAKE_SOURCE_DIR}/pluginspec
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/ext/cpr-1.9.1/include
    ${CMAKE_SOURCE_DIR}/ext/seasocks-1.4.4/src/main/c

)

add_executable(mainserver main.cpp)
target_compile_features(mainserver PUBLIC cxx_std_17)

target_link_libraries(mainserver td seasocks)

