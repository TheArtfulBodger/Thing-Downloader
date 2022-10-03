cmake_minimum_required(VERSION 3.10)

include_directories(
    ${CMAKE_SOURCE_DIR}/pluginspec
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/ext/cpr-1.9.1/include
    ${CMAKE_SOURCE_DIR}/ext/tinyxml2-9.0.0
    ${CMAKE_SOURCE_DIR}/ext/gumbo-query/src
    ${CMAKE_SOURCE_DIR}/ext/gumbo-parser-0.10.1/src
    ${CMAKE_SOURCE_DIR}/ext/tiny-process-library-v2.0.4

)

add_library(operavision SHARED details.cpp get_jobs.cpp should_skip.cpp download_description.cpp download_video.cpp)
target_compile_features(operavision PUBLIC cxx_std_17)
target_link_libraries(operavision cpr::cpr tinyxml gumbo tiny-process-library)