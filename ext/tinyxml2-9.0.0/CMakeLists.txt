cmake_minimum_required(VERSION 3.10)

add_library(tinyxml STATIC tinyxml2.cpp)
set_target_properties(tinyxml PROPERTIES POSITION_INDEPENDENT_CODE ON)
