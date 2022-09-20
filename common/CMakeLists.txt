cmake_minimum_required(VERSION 3.10)

add_library(td
    src/plugin.cpp
    src/web/manager/thread_loop.cpp
    src/web/manager/thin.cpp
    src/web/manager/downloader.cpp
    src/web/job.cpp
    src/minimal_downloader.cpp
    src/json_store.cpp
)

target_include_directories(td PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/pluginspec
)

target_link_libraries(td dl)

add_library(td_rpc
    src/web/rpc/handler.cpp
    src/web/rpc/populate_functions.cpp

    src/web/rpc/functions/get_jobs.cpp
)

target_include_directories(td_rpc PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/pluginspec
    ${CMAKE_SOURCE_DIR}/ext/seasocks-1.4.4/src/main/c
)

target_link_libraries(td_rpc td dl seasocks)

install(TARGETS td td_rpc
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})