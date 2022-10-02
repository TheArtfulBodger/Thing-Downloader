cmake_minimum_required(VERSION 3.10)

include_directories(
    ${CMAKE_SOURCE_DIR}/pluginspec
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/ext/cpr-1.9.1/include

)

add_executable(tdd main.cpp static_serve.cpp)
target_compile_features(tdd PUBLIC cxx_std_17)

target_link_libraries(tdd td td_rpc ixwebsocket)

install(TARGETS tdd
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})