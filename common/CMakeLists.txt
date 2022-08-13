cmake_minimum_required(VERSION 3.10)

add_library(td
    src/plugin.cpp
    src/web/manager/thread_loop.cpp
    src/web/manager/thin.cpp
    src/web/manager/downloader.cpp
    src/minimal_downloader.cpp
    src/json_store.cpp
)

target_include_directories(td PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/pluginspec
)

target_link_libraries(td dl)