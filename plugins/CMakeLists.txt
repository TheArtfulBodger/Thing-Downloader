cmake_minimum_required(VERSION 3.10)

add_subdirectory(operavision)
add_subdirectory(itchio)

include_directories(
    ${CMAKE_SOURCE_DIR}/pluginspec
    ${CMAKE_SOURCE_DIR}/ext
    ${CMAKE_SOURCE_DIR}/ext/cpr-1.9.1/include

)

add_library(identity SHARED identity.cpp)
target_compile_features(identity PUBLIC cxx_std_17)

add_library(apod SHARED apod.cpp)
target_compile_features(apod PUBLIC cxx_std_17)
target_link_libraries(apod cpr::cpr)

