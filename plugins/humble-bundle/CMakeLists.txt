cmake_minimum_required(VERSION 3.10)

include_directories(
  ${CMAKE_SOURCE_DIR}/pluginspec
  ${CMAKE_SOURCE_DIR}/ext
  ${CMAKE_SOURCE_DIR}/ext/cpr-1.9.1/include
  ${CMAKE_SOURCE_DIR}/ext/gumbo-query/src
  ${CMAKE_SOURCE_DIR}/ext/gumbo-parser-0.10.1/src)

add_library(humble-bundle SHARED details.cpp get_jobs.cpp should_skip.cpp
                                 download.cpp)
target_compile_features(humble-bundle PUBLIC cxx_std_17)
target_link_libraries(humble-bundle cpr::cpr gumbo)
