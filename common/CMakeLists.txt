cmake_minimum_required(VERSION 3.10)

add_library(td STATIC
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
if(NOT WIN32)
target_link_libraries(td dl pthread)
endif()
target_compile_features(td PUBLIC cxx_std_17)

add_library(td_rpc STATIC
    src/web/rpc/handler.cpp
    src/web/rpc/populate_functions.cpp

    src/web/rpc/functions/get_jobs.cpp
    src/web/rpc/functions/plugins.cpp
)

target_include_directories(td_rpc PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/pluginspec
    ${CMAKE_SOURCE_DIR}/ext/IXWebSocket
)

target_link_libraries(td_rpc td ixwebsocket)
if(NOT WIN32)
target_link_libraries(td_rpc dl pthread)
endif()
target_compile_features(td_rpc PUBLIC cxx_std_17)

install(TARGETS td td_rpc
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})