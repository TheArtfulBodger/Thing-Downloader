cmake_minimum_required(VERSION 3.10)

add_executable(td-test
    main.cpp
    minimal_downloader.cpp
)

target_include_directories(td-test PUBLIC
    ${CMAKE_SOURCE_DIR}/common/include
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/pluginspec

)

target_link_libraries(td-test
    td
)

target_compile_features(td-test PUBLIC cxx_std_17)
