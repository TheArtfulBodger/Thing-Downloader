cmake_minimum_required(VERSION 3.10)

# Add External Dependencies via a "add_subdirectory" call.
if(NOT MSVC)
set(CPR_FORCE_USE_SYSTEM_CURL ON CACHE BOOL "Force Use of System curl")
endif()
add_subdirectory(cpr-1.9.1)

add_subdirectory(seasocks-1.4.4)
add_subdirectory(tinyxml2-9.0.0)

include(gumbo.cmake)
include(zlib.cmake)

install(TARGETS gumbo tinyxml
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})