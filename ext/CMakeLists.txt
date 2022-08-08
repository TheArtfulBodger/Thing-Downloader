cmake_minimum_required(VERSION 3.10)

# Add External Dependencies via a "add_subdirectory" call.
add_subdirectory(cpr-1.9.1)
add_subdirectory(tinyxml2-9.0.0)
include(gumbo.cmake)