cmake_minimum_required(VERSION 3.10)

include_directories(
    ${CMAKE_SOURCE_DIR}/pluginspec
)

add_library(identity SHARED identity.cpp)
target_compile_features(identity PUBLIC cxx_std_17)
