cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_SOURCE_DIR}/pluginspec ${CMAKE_SOURCE_DIR}/ext
                    ${CMAKE_SOURCE_DIR}/ext/cpr-1.9.1/include)

add_library(itchio SHARED details.cpp get_jobs.cpp should_skip.cpp
                          load_games.cpp download_file.cpp)
target_compile_features(itchio PUBLIC cxx_std_17)
target_link_libraries(itchio cpr::cpr)
