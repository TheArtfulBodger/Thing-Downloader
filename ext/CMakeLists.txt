cmake_minimum_required(VERSION 3.10)

# Add External Dependencies via a "add_subdirectory" call.
if(NOT MSVC)
set(CPR_FORCE_USE_SYSTEM_CURL ON CACHE BOOL "Force Use of System curl")
endif()
add_subdirectory(cpr-1.9.1)

if(MSVC)
set(USE_ZLIB OFF)
set(BUILD_SHARED_LIBS ON)
endif()
add_subdirectory(IXWebSocket)
add_subdirectory(tinyxml2-9.0.0)

include(gumbo.cmake)

install(TARGETS gumbo tinyxml
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})