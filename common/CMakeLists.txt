cmake_minimum_required(VERSION 3.10)

add_library(td
    src/plugin.cpp
)

target_include_directories(td PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/pluginspec
)

target_link_libraries(td dl)